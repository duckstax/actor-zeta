#ifndef BLOCKING_ACTOR_HPP
#define BLOCKING_ACTOR_HPP

#include "local_actor.hpp"

namespace actor_model {
    class blocking_actor : public local_actor {
    public:

        blocking_actor(const std::string &type, behavior &live, abstract_coordinator_ptr e)
                : local_actor(type, live, e) { is_blocked(true);}

        void act() {

        }
    };
}
#endif //BLOCKING_ACTOR_HPP
