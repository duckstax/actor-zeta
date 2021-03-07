#include <actor-zeta/base/actor_address.hpp>

namespace actor_zeta { namespace base {

      actor_address::actor_address(communication_module *aa) : ptr_(aa) {}

      actor_address::~actor_address() {}

}}
