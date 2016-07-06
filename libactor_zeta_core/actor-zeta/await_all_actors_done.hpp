#ifndef AWAIT_ALL_ACTORS_DONE_HPP
#define AWAIT_ALL_ACTORS_DONE_HPP

#include <actor-zeta/actor/actor.hpp>
#include "forwards.hpp"

namespace actor_zeta {

    void await_all_actors_done(environment::group &g);

    void await_all_actors_done(environment::cooperation &c);

    void await_all_actors_done(actor::actor &a);

}
#endif //AWAIT_ALL_ACTORS_DONE_HPP
