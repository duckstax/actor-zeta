#ifndef AWAIT_ALL_ACTORS_DONE_HPP
#define AWAIT_ALL_ACTORS_DONE_HPP

#include "forwards.hpp"

namespace actor_zeta {

    void await_all_actors_done(group &g);

    void await_all_actors_done(cooperation &c);

    void await_all_actors_done(actor &a);

}
#endif //AWAIT_ALL_ACTORS_DONE_HPP
