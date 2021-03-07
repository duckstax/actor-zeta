#include <utility>

#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>


namespace actor_zeta { namespace base {

        auto message::command() const noexcept -> detail::string_view {
            return detail::string_view(command_.data(),command_.size());
        }

        auto message::clone() const -> message* {
            return new message(sender_,command_,body_);
        }

        message::operator bool() {
            return !command_.empty() || bool(sender_) || body_.has_value();
        }

        message::message(base::actor_address sender, std::string name)
            : sender_(std::move(sender))
            , command_(std::move(name))
            , body_() {}

        message::message(base::actor_address sender, std::string name, detail::any body)
            : sender_(std::move(sender))
            , command_(std::move(name))
            , body_(std::move(body)) {}

        auto message::sender() const -> base::actor_address {
            return sender_;
        }

        void message::swap(message &other) noexcept {
            using std::swap;
            swap(sender_,other.sender_);
            swap(command_,other.command_);
            swap(body_, other.body_);
        }

        message::message():next(nullptr),prev(nullptr) {}

        bool message::is_high_priority() const {
            return false;
        }

        auto message::body() -> detail::any & {
            assert(body_.has_value());
            return body_;
        }
}}
