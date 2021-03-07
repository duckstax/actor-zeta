#include <utility>

#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message_header.hpp>
#include <actor-zeta/base/message.hpp>


namespace actor_zeta { namespace base {

        auto message::command() const noexcept -> detail::string_view {
            return header_.command();
        }

        auto message::clone() const -> message* {
            return new message(header_,body_);
        }

        message::operator bool() {
            return bool(header_) || body_.has_value();
        }

        message::message(base::actor_address sender_, std::string name):
            header_(std::move(sender_),std::move(name)),
            body_() {
        }

        message::message(base::actor_address sender_, std::string name, detail::any body):
            header_(std::move(sender_),std::move(name)),
            body_(std::move(body)) {}

        message::message(const message_header &header, const detail::any &body):
            header_(header),
            body_(body) {}


        auto message::sender() const -> base::actor_address {
            return header_.sender();
        }

        void message::swap(message &other) noexcept {
            using std::swap;
            swap(header_, other.header_);
            swap(body_, other.body_);
        }

        message::message():next(nullptr),prev(nullptr) {}

        auto message::body() -> detail::any & {
            assert(body_.has_value());
            return body_;
        }
}}
