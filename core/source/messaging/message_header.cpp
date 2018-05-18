#include <utility>
#include "actor-zeta/messaging/message_header.hpp"

namespace actor_zeta {
    namespace messaging {

        auto message_header::command() const -> const behavior::type_action & {
            return command_;
        }

        message_priority message_header::priorities() const {
            return prioritie;
        }

        message_header::message_header(actor::actor_address sender_,const std::string& name)
                :sender_(std::move(sender_)), command_(name), prioritie(message_priority::normal) {}

        message_header::message_header(actor::actor_address sender_,const std::string& name, message_priority p)
                :sender_(std::move(sender_)), command_(name), prioritie(p) {}

        auto message_header::sender() const -> actor::actor_address {
            return sender_;
        }


    }
}