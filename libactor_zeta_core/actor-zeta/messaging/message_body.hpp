#ifndef MESSAGE_BODY_HPP
#define MESSAGE_BODY_HPP

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
        class message_body final {
        public:
            constexpr message_body() noexcept: content(nullptr) {}

            template<typename ValueType>
            message_body(const ValueType &value): content(new holder<ValueType>(value)) {}

            message_body(const message_body &other) : content(other.content ? other.content->clone() : nullptr) {}

            message_body(message_body &&other) noexcept : content(other.content) {
                other.content = nullptr;
            }

            template<typename ValueType>
            message_body(ValueType &&value) : content(new holder<ValueType>(std::move(value))) {}


            ~message_body() noexcept {
                delete content;
            }

            message_body &swap(message_body &rhs) noexcept {
                std::swap(content, rhs.content);
                return *this;
            }

            message_body &operator=(const message_body &rhs) {
                message_body(rhs).swap(*this);
                return *this;
            }

            message_body &operator=(message_body &&rhs)noexcept {
                rhs.swap(*this);
                message_body().swap(rhs);
                return *this;
            }

            template<class ValueType>
            message_body &operator=(ValueType &&rhs) {
                message_body(std::move(rhs)).swap(*this);
                return *this;
            }

            bool empty() const noexcept {
                return !content;
            }

            void clear() noexcept {
                message_body().swap(*this);
            }

            template<typename T>
            T get() {
                return static_cast<holder <T> *>(content)->held;
            }

        private:

            struct placeholder {
                virtual ~placeholder() {}

                virtual placeholder *clone() const = 0;
            };

            template<typename ValueType>
            struct holder : public placeholder {


                holder(const ValueType &value) : held(value) {
                }

                holder(ValueType &&value) : held(std::move(value)) {
                }

                virtual placeholder *clone() const {
                    return new holder(held);
                }

                ValueType held;

                holder &operator=(const holder &) = delete;
            };

        private:
            placeholder *content;
        };

    }
}

inline void swap(actor_zeta::messaging::message_body &lhs, actor_zeta::messaging::message_body &rhs)noexcept {
    lhs.swap(rhs);
}


#endif //MESSAGE_BODY_HPP
