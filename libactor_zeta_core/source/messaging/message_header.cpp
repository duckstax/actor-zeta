#include <MacTypes.h>
#include "actor-zeta/messaging/message_header.hpp"

namespace actor_zeta {
    namespace messaging {
        message_header::message_header(const char *str, std::size_t len)
                : type_(str, len),  prioritie(message_priority::normal), callback(false) {}

        message_header::message_header(const char *str, std::size_t len, actor::actor_address aa)
                : type_(str, len),  prioritie(message_priority::normal), callback(true), address(aa) {}

        message_header::message_header(const char *str, std::size_t len, message_priority p)
                :type_(str, len),  prioritie(p), callback(false) {}

        message_header::message_header(const char *str, std::size_t len, message_priority p, actor::actor_address aa)
                : type_(str, len), prioritie(p), callback(true), address(aa) {}

        auto message_header::type() const -> const behavior::type_action & {
            return type_;
        }

        actor::actor_address message_header::return_address() const {
            return address;
        }

        bool message_header::is_callback() const {
            return callback;
        }

        message_priority message_header::priorities() const {
            return prioritie;
        }
    }
}