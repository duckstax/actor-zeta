#ifndef BEHAVIOR_RESPONSE_HPP
#define BEHAVIOR_RESPONSE_HPP

#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace behavior {
///
/// @brief This is a response container for messaging
///
        class response {
        private:
            actor::actor_address receiver_;
            messaging::message *msg;
        public:
            response() = default;

            response(const response &) = default;

            response &operator=(const response &) = default;

            response(response &&) = default;

            response &operator=(response &&) = default;

            ~response() = default;

            response(actor::actor_address receiver_, messaging::message *msg) : receiver_(receiver_), msg(msg) {}

            messaging::message *message() {
                return msg;
            };

            actor::actor_address receiver() const {
                return receiver_;
            }
        };

        inline response * make_response(actor::actor_address receiver_, messaging::message *msg){
            return new response(receiver_, msg);
        }
    }
}
#endif //RESPONSE_HPP
