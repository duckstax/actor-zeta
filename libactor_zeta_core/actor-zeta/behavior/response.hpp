#ifndef BEHAVIOR_RESPONSE_HPP
#define BEHAVIOR_RESPONSE_HPP

#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace behavior {
///
/// @brief Represents input message entity
///
        class response {
        public:
            response();

            response(const response &) = delete;

            response &operator=(const response &) = delete;

            response(response &&);

            response &operator=(response &&);

            ~response();

            response(actor::actor_address receiver_, messaging::message &&msg);

            messaging::message message();

            actor::actor_address receiver() const;

            operator bool();

        private:
            struct impl;
            std::unique_ptr<impl> pimpl;
        };

        inline response make_response(actor::actor_address receiver_, messaging::message&& msg){
            return response(receiver_, std::move(msg));
        }
    }
}
#endif //RESPONSE_HPP
