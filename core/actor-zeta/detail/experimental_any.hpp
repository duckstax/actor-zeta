#pragma once

#include <new>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <actor-zeta/detail/type_traits.hpp>

namespace actor_zeta {
    namespace detail {
///
/// @brief
///

/// Drop-in replacement for C++17 std::any.
        template<class T>
        struct in_place_type_tag final {};

        template<std::size_t K>
        struct in_place_index_tag final {};

        struct in_place_t {};

        template<class T>
        inline in_place_t in_place_type(in_place_type_tag<T> = in_place_type_tag<T>()) {
            return in_place_t();
        }

        template<std::size_t K>
        inline in_place_t in_place_index(in_place_index_tag<K> = in_place_index_tag<K>()) {
            return in_place_t();
        }


#define lite_in_place_type_t(T) in_place_t(&)( in_place_type_tag<T>  )
#define lite_in_place_type(T)   in_place_type<T>


class enabler final {};
#define requires(...) \
, typename = typename std::enable_if< (__VA_ARGS__), enabler >::type

        class any final {
        public:
            constexpr any() noexcept: content(nullptr) {}

            any(any const &other) : content(other.content ? other.content->clone() : nullptr) {}

            any(any &&other) noexcept : content(other.content) {
                other.content = nullptr;
            }

            template<
                    class ValueType,
                    class T = typename std::decay<ValueType>::type requires(! std::is_same<T, any>::value )>
            any(ValueType &&value) noexcept : content(new holder<T>(std::move(value))) {}

            template<
                    class T,
                    class... Args requires(std::is_constructible<T, Args && ...>::value)>
            explicit any( lite_in_place_type_t(T), Args&&... args ):
                content( new holder<T> ( T(std::forward<Args>(args)...))){

            }

            template<
                    class T,
                    class U,
                    class... Args requires(std::is_constructible<T, std::initializer_list<U> &, Args && ...>::value)
            >
            explicit any(lite_in_place_type_t(T), std::initializer_list<U> il, Args &&... args):
                content(new holder<T>(T(il, std::forward<Args>(args)...))) {

            }

            ~any() {
                reset();
            }

            any &operator=(any const &other) {
                any(other).swap(*this);
                return *this;
            }

            any &operator=(any &&other) noexcept {
                any(std::move(other)).swap(*this);
                return *this;
            }

            template<class ValueType, class T = typename std::decay<ValueType>::type requires(! std::is_same<T, any>::value )>
            any &operator=(ValueType &&value) {
                any(std::move(value)).swap(*this);
                return *this;
            }

            template<class T, class... Args>
            void emplace(Args &&... args) {
                any(T(std::forward<Args>(args)...)).swap(*this);
            }

            template<class T, class U, class... Args requires(std::is_constructible<T, std::initializer_list<U> &, Args && ...>::value)>
            void emplace(std::initializer_list<U> il, Args &&... args) {
                any(T(il, std::forward<Args>(args)...)).swap(*this);
            }

            void reset() noexcept {
                delete content;
                content = nullptr;
            }

            void swap(any &other) noexcept {
                std::swap(content, other.content);
            }

            bool has_value() const noexcept {
                return content != nullptr;
            }

            /// non-standard:
            template<class ValueType>
            const ValueType *to_ptr() const {
                if(content == nullptr){
                    return nullptr;
                } else {
                    return &(static_cast<holder <ValueType> *>( content )->held);
                }
            }

            template<class ValueType>
            ValueType *to_ptr() {
                if(content == nullptr){
                    return nullptr;
                } else {
                    return &(static_cast<holder <ValueType> *>( content )->held);
                }
            }

        private:
            class placeholder {
            public:
                virtual ~placeholder() = default;

                virtual placeholder *clone() const = 0;
            };

            template<typename ValueType>
            class holder final : public placeholder {
            public:
                holder(ValueType const &value): held(value) {}

                holder(ValueType &&value) : held(std::move(value)) {}

                placeholder *clone() const override {
                    return new holder(held);
                }

                ValueType held;
            };

            placeholder *content;
        };

        inline void swap(any &x, any &y) noexcept {
            x.swap(y);
        }

        template<class T, class ...Args>
        inline any make_any(Args &&...args) {
            return any(lite_in_place_type(T), std::forward<Args>(args)...);
        }

        template<class T, class U, class ...Args>
        inline any make_any(std::initializer_list<U> il, Args &&...args) {
            return any(lite_in_place_type(T), il, std::forward<Args>(args)...);
        }


        template<class ValueType//,
                //typename = typename std::enable_if<(
                //std::is_reference<ValueType>::value ||
                //std::is_copy_constructible<ValueType>::value), enabler>::type
        >
        inline ValueType any_cast(any const &operand) {
            const ValueType *result = any_cast<typename std::add_const<typename std::remove_reference<ValueType>::type>::type>(&operand);
            assert(result);
            return *result;
        }

        template<
                class ValueType//,
                //typename = typename std::enable_if<(std::is_reference<ValueType>::value ||
                //                                                     std::is_copy_constructible<ValueType>::value), enabler>::type

        >
        inline ValueType any_cast(any &operand) {
            const ValueType *result = any_cast<typename std::remove_reference<ValueType>::type>(&operand);
            assert(result);
            return *result;
        }

        template<
                class ValueType
                //requires(std::is_reference<ValueType>::value || std::is_copy_constructible<ValueType>::value )
        >

        inline ValueType any_cast(any &&operand) {
            const ValueType *result = any_cast<typename std::remove_reference<ValueType>::type>(&operand);
            assert(result);
            return *result;
        }


        template<class ValueType>
        inline ValueType const *any_cast(any const *operand) noexcept {
            return operand != nullptr ? operand->to_ptr<ValueType>() : nullptr;
        }

        template<class ValueType>
        inline ValueType *any_cast(any *operand) noexcept {
            return operand != nullptr ? operand->to_ptr<ValueType>() : nullptr;
        }
}}
