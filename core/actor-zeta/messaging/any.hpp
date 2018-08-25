#pragma once

#include <new>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <algorithm>

namespace actor_zeta {
    namespace messaging {
///
/// @brief
///
        class any final {
        public:
            constexpr any() noexcept: content(nullptr) {}

            template<typename ValueType>
            any(const ValueType &value): content(new holder<ValueType>(value)) {}

            any(const any &other) : content(other.content ? other.content->clone() : nullptr) {}

            any(any &&other) noexcept : content(other.content) {
                other.content = nullptr;
            }

            template<typename ValueType>
            any(ValueType &&value) : content(new holder<ValueType>(std::forward<ValueType>(value))) {}


            ~any() noexcept {
                delete content;
            }

            any &swap(any &rhs) noexcept {
                using std::swap;
                std::swap(content, rhs.content);
                return *this;
            }

            any &operator=(const any &rhs) {
                any(rhs).swap(*this);
                return *this;
            }

            any &operator=(any &&rhs)noexcept {
                rhs.swap(*this);
                any().swap(rhs);
                return *this;
            }

            template<class ValueType>
            any &operator=(ValueType &&rhs) {
                any(std::forward<ValueType>(rhs)).swap(*this);
                return *this;
            }

            bool empty() const noexcept {
                return content == nullptr;
            }

            void clear() noexcept {
                any().swap(*this);
            }

            template<typename T>
            T get() {
                return static_cast<holder <T> *>(content)->held;
            }

        private:

            struct placeholder {
                virtual ~placeholder() = default;

                virtual placeholder *clone() const = 0;
            };

            template<typename ValueType>
            struct holder final : placeholder {


                holder(const ValueType &value) : held(value) {
                }

                holder(ValueType &&value) : held(std::move(value)) {
                }

                placeholder *clone() const override  {
                    return new holder(held);
                }

                ValueType held;

                ~holder() override  = default;

                holder &operator=(const holder &) = delete;
            };
        private:
            placeholder *content;
        };

    }
}

inline void swap(actor_zeta::messaging::any &lhs, actor_zeta::messaging::any &rhs)noexcept {
    lhs.swap(rhs);
}
