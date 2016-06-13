#ifndef BROKER_HPP
#define BROKER_HPP

#include "actor-zeta/actor/local_actor.hpp"
#include "multiplexer.hpp"
#include "actor-zeta/connection_handler.hpp"

namespace actor_zeta {
    namespace network {
        class broker : public actor_zeta::local_actor {
        public:
            broker(const std::string &);

            virtual ~broker() = default;

        private:
            std::map<std::string, write_handler> actions;
        };
    }
}
#endif //ABSTRACT_BROKER_HPP
