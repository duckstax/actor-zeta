
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

            impl(actor::actor_address sender_,const std::string& name, any &&body)
                    :header_(std::move(sender_),name),body_(std::move(body)) {}

            impl(message_header header, const any &body)
                    :header_(std::move(header)),body_(body) {}

            message_header header_;
            any   body_;

        };
        
        auto message::command() const noexcept -> const behavior::type_action & {
            return pimpl->header_.command();
        }

        auto message::clone() const -> message {
            return message(pimpl->header_,pimpl->body_);
        }

        message::operator bool() {
            return bool(pimpl);
        }

        auto message::get_body() -> any & {
            return pimpl->body_;
        }

        message::message(actor::actor_address sender_,const std::string& name, any &&body)
                :pimpl(new impl(std::move(sender_),name,std::move(body))) {}

        message::message(const message_header &header, const any &body):pimpl(new impl(header,body)) {}


        auto message::sender() const -> actor::actor_address {
            return pimpl->header_.sender();
        }

        message::~message() = default;

        message::message() = default;

        message::message(message &&other) noexcept = default;

        message &message::operator=(message &&) noexcept = default;
    }
}
