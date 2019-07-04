#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta { namespace actor {

      actor_address::actor_address(abstract_actor *aa) : ptr_(aa) {}

      actor_address::~actor_address() {}

}}
