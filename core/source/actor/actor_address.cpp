#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta { namespace actor {

      actor_address::actor_address(abstract_async_container *aa) : ptr_(aa) {}

      actor_address::~actor_address() {}

}}
