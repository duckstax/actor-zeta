#include <utility>
#include "actor-zeta/messaging/message_header.hpp"

namespace actor_zeta {
    namespace messaging {

        auto message_header::command() const -> const behavior::type_action & {
            return command_;
        }

        message_header::message_header(actor::actor_address sender_,const std::string& name)
                :sender_(std::move(sender_)), command_(name) {}

        auto message_header::sender() const -> actor::actor_address {
            return sender_;
        }


    }
}