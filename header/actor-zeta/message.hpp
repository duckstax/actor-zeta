#pragma once

#include <cassert>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta {

///
/// @brief
///
        class message final {
        public:
            message() = default;

            message(const message &) = delete;

            message &operator=(const message &) = delete;

            message(message &&other) = default;

            message &operator=(message &&) = default;

            ~message() = default;

            message(address_t /*sender*/, detail::string_view /*name*/);

            message(address_t /*sender*/, detail::string_view /*name*/, detail::any /*body*/);

            auto command() const noexcept -> detail::string_view;

            auto sender() const -> address_t;

            template<typename T>
            auto body() const -> const T& {
                assert(body_.has_value());
                return detail::any_cast<const T&>(body_);
            }

            template<typename T>
            auto body() -> T& {
                assert(body_.has_value());
                return detail::any_cast<T&>(body_);
            }

            auto body() -> detail::any&;

            auto clone() const -> message;

            operator bool();

            void swap(message& other) noexcept;

        private:
            address_t sender_;
            detail::string_view command_;
            detail::any  body_;
        };

}

inline void swap(actor_zeta::message &lhs, actor_zeta::message &rhs) noexcept {
    lhs.swap(rhs);
}
