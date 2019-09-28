#include <actor-zeta/actor/supervisor.hpp>

namespace actor_zeta { namespace actor {

        supervisor::supervisor(detail::string_view name):base_actor(name) {
            type_.type = abstract::supervisor;
        }

        supervisor::~supervisor() {}

}}