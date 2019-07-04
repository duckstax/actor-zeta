
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/messaging/message_header.hpp>
#include <utility>
#include <actor-zeta/messaging/message.hpp>


namespace actor_zeta { namespace messaging {

        auto message::command() const noexcept -> detail::string_view {
            return header_.command();
        }

        auto message::clone() const -> message {
            return message(header_,body_);
        }

        message::operator bool() {
            return init;
        }

        message::message(actor::actor_address sender_,std::string name, detail::any &&body):
            init(true),
            header_(std::move(sender_),std::move(name)),
            body_(std::move(body)) {}

        message::message(const message_header &header, const detail::any &body):
            init(true),
            header_(header),
            body_(body) {}


        auto message::sender() const -> actor::actor_address {
            return header_.sender();
        }

        message::message():init(false),header_(),body_() {

        }

        void message::swap(message &other) noexcept {
            using std::swap;
            swap(header_, other.header_);
            swap(body_, other.body_);
        }
    }
}
