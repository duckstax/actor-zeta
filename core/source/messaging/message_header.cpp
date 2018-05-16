#include "actor-zeta/messaging/message_header.hpp"

namespace actor_zeta {
    namespace messaging {

        auto message_header::command() const -> const behavior::type_action & {
            return command_;
        }

        actor::actor_address message_header::recipient() const {
            return recipient_;
        }

        message_priority message_header::priorities() const {
            return prioritie;
        }

        message_header::message_header(actor::actor_address sender_,const std::string& name)
                :sender_(sender_), command_(name), prioritie(message_priority::normal) {}

        message_header::message_header(actor::actor_address sender_,const std::string& name, actor::actor_address aa)
                :sender_(sender_),recipient_(aa), command_(name), prioritie(message_priority::normal) {}

        message_header::message_header(actor::actor_address sender_,const std::string& name, message_priority p)
                :sender_(sender_), command_(name), prioritie(p) {}

        message_header::message_header(actor::actor_address sender_,const std::string& name, message_priority p, actor::actor_address aa)
                :sender_(sender_), recipient_(aa),command_(name), prioritie(p) {}

        auto message_header::sender() const -> actor::actor_address {
            return sender_;
        }


    }
}