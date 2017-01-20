
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace messaging {

        actor::actor_address actor_zeta::messaging::message::return_address() const {
            return header_.return_address();
        }

        bool message::is_callback() const {
            return header_.is_callback();
        }

        message_priority message::priority() const {

            return header_.priorities();
        }

        auto message::type() const -> const behavior::type_action & {
            return header_.type();
        }
    }
}
