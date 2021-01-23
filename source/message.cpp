#include <utility>

#include <address_t.hpp>
#include <message.hpp>

namespace actor_zeta {

        auto message::command() const noexcept -> detail::string_view {
            return command_;
        }

        auto message::clone() const -> message {
            return message(sender_,command_,body_);
        }

        message::operator bool() {
            return (bool(sender_) && bool(!command_.empty())) || body_.has_value();
        }

        message::message(address_t sender, detail::string_view name):
            sender_(sender),
            command_(name),
            body_() {
        }

        message::message(address_t sender, detail::string_view name, detail::any body):
            sender_(sender),
            command_(name),
            body_(std::move(body)) {}


        auto message::sender() const -> address_t {
            return sender_;
        }

        void message::swap(message &other) noexcept {
            using std::swap;
            swap(sender_, other.sender_);
            swap(command_, other.command_);
            swap(body_, other.body_);
        }

        auto message::body() -> detail::any & {
            assert(body_.has_value());
            return body_;
        }
}
