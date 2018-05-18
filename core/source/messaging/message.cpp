
#include "actor-zeta/messaging/message.hpp"
#include <actor-zeta/messaging/message_header.hpp>
#include <utility>

namespace actor_zeta {
    namespace messaging {

        struct message::impl final {
            impl() = default;
            impl(impl&&)= default;
            impl&operator=(impl&&)= default;
            impl(const impl &t) = delete;
            impl &operator=(const impl &t) = delete;
            ~impl() = default;

            impl(actor::actor_address sender_,const std::string& name, message_body &&body)
                    :header_(std::move(sender_),name),body_(std::move(body)) {}

            impl(actor::actor_address sender_,const std::string& name, message_body &&body, message_priority priority)
                    :header_(std::move(sender_),name,priority),body_(std::move(body)) {}


            impl(message_header header, const message_body &body)
                    :header_(std::move(header)),body_(body) {}

            message_header header_;
            message_body   body_;

        };

        message_priority message::priority() const {

            return pimpl->header_.priorities();
        }

        auto message::command() const -> const behavior::type_action & {
            return pimpl->header_.command();
        }

        auto message::clone() const -> message {
            return message(pimpl->header_,pimpl->body_);
        }

        message::operator bool() {
            return bool(pimpl);
        }

        auto message::get_body() -> message_body & {
            return pimpl->body_;
        }

        message::message(actor::actor_address sender_,const std::string& name, message_body &&body)
                :pimpl(new impl(std::move(sender_),name,std::move(body))) {}

        message::message(actor::actor_address sender_,const std::string& name, message_body &&body, message_priority priority)
                :pimpl(new impl(std::move(sender_),name,std::move(body),priority)) {}

        message::message(const message_header &header, const message_body &body):pimpl(new impl(header,body)) {}


        auto message::sender() const -> actor::actor_address {
            return pimpl->header_.sender();
        }

        message::~message() = default;

        message::message() = default;

        message::message(message &&other) = default;

        message &message::operator=(message &&)  = default;
    }
}
