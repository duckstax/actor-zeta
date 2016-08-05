#ifndef BROKER_HPP
#define BROKER_HPP

#include <unordered_map>

#include "actor-zeta/actor/local_actor.hpp"
#include "multiplexer.hpp"
#include "actor-zeta/connection_handler.hpp"

namespace actor_zeta {
    namespace network {
        class broker : public actor_zeta::actor::local_actor {
        public:
            broker(environment::environment &, const std::string &);

            virtual ~broker() = default;

        protected:
            void initialize();

            std::unordered_map<std::string, write_handler> actions;
        };
    }
}
#endif //ABSTRACT_BROKER_HPP
