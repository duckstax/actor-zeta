#include <actor-zeta/actor/supervisor.hpp>

namespace actor_zeta { namespace actor {

        auto link(supervisor &g1, supervisor &g2) -> void {
            g1.join(g2);
            g2.join(g1);
        }

        supervisor::supervisor(detail::string_view name):base_actor(name) {
            type_.type = abstract::supervisor;
        }

        supervisor::~supervisor() {}

}}