#pragma once

#include <cassert>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/messaging/message_header.hpp>

namespace actor_zeta { namespace messaging {

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

            message(base::actor_address /*sender*/, std::string /*name*/);

            message(base::actor_address /*sender*/, std::string /*name*/, detail::any /*body*/);

            auto command() const noexcept -> detail::string_view;

            auto sender() const -> base::actor_address ;

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
            message(const message_header &header, const detail::any &body);

            message_header header_;

            detail::any  body_;
        };

}}

inline void swap(actor_zeta::messaging::message &lhs, actor_zeta::messaging::message &rhs) noexcept {
    lhs.swap(rhs);
}
