#ifndef AWAIT_ALL_ACTORS_DONE_HPP
#define AWAIT_ALL_ACTORS_DONE_HPP

#include "fwd.hpp"

namespace actor_model {

    void await_all_actors_done(group &g);

    void await_all_actors_done(cooperation &c);

    void await_all_actors_done(actor &a);

}
#endif //AWAIT_ALL_ACTORS_DONE_HPP
