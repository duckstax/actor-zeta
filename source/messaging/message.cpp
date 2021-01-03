#include <utility>

#include <actor-zeta/base/address_type.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/messaging/message_header.hpp>

namespace actor_zeta { namespace messaging {

        auto message::command() const noexcept -> detail::string_view {
            return header_.command();
        }

        auto message::clone() const -> message {
            return message(header_,body_);
        }

        message::operator bool() {
            return bool(header_) || body_.has_value();
        }

        message::message(base::address_type sender_, detail::string_view name):
            header_(std::move(sender_),std::move(name)),
            body_() {
        }

        message::message(base::address_type sender_, detail::string_view name, detail::any body):
            header_(std::move(sender_),std::move(name)),
            body_(std::move(body)) {}

        message::message(const message_header &header, const detail::any &body):
            header_(header),
            body_(body) {}


        auto message::sender() const -> base::address_type {
            return header_.sender();
        }

        void message::swap(message &other) noexcept {
            using std::swap;
            swap(header_, other.header_);
            swap(body_, other.body_);
        }

        auto message::body() -> detail::any & {
            assert(body_.has_value());
            return body_;
        }
}}
