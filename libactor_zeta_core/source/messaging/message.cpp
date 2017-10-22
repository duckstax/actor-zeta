
#include "actor-zeta/messaging/message.hpp"
#include <actor-zeta/messaging/message_header.hpp>

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
                    :header_(sender_,name),body_(std::move(body)) {}

            impl(actor::actor_address sender_,const std::string& name, message_body &&body, actor::actor_address address)
                    :header_(sender_,name,address),body_(std::move(body)) {}

            impl(actor::actor_address sender_,const std::string& name, message_body &&body, message_priority priority)
                    :header_(sender_,name,priority),body_(std::move(body)) {}

            impl(actor::actor_address sender_,const std::string& name, message_body &&body, message_priority priority, actor::actor_address address)
                    :header_(sender_,name,priority,address),body_(std::move(body)) {}

            impl(const message_header &header, const message_body &body)
                    :header_(header),body_(body) {}

            message_header header_;
            message_body   body_;

        };

        bool message::is_callback() const {
            return pimpl->header_.is_callback();
        }

        message_priority message::priority() const {

            return pimpl->header_.priorities();
        }

        auto message::type() const -> const behavior::type_action & {
            return pimpl->header_.type();
        }

        auto message::clone() const -> message {
            return message(pimpl->header_,pimpl->body_);
        }

        message::operator bool() {
            return !pimpl;
        }

        auto message::get_body() -> message_body & {
            return pimpl->body_;
        }

        message::message(actor::actor_address sender_,const std::string& name, message_body &&body)
                :pimpl(new impl(sender_,name,std::move(body))) {}

        message::message(actor::actor_address sender_,const std::string& name, message_body &&body, actor::actor_address aa)
                :pimpl(new impl(sender_,name,std::move(body),aa)) {}

        message::message(actor::actor_address sender_,const std::string& name, message_body &&body, message_priority priority)
                :pimpl(new impl(sender_,name,std::move(body),priority)) {}

        message::message(actor::actor_address sender_,const std::string& name, message_body &&body, message_priority priority, actor::actor_address address)
                :pimpl(new impl(sender_,name,std::move(body),priority,address)) {}

        message::message(const message_header &header, const message_body &body):pimpl(new impl(header,body)) {}

        auto message::recipient() const -> actor::actor_address {
            return pimpl->header_.recipient();
        }

        auto message::sender() const -> actor::actor_address {
            return pimpl->header_.sender();
        }

        message::~message() = default;

        message::message() = default;

        message::message(message &&other) = default;

        message &message::operator=(message &&)  = default;
    }
}
