#include "actor-zeta/broker.hpp"
#include "actor-zeta/standard_handlers/write.hpp"
#include "actor-zeta/standard_handlers/add_write.hpp"

namespace actor_zeta {
    namespace network {

        broker::broker(environment::environment &env,const std::string &name) : local_actor(env, name) {
            initialize();
        }

        void broker::initialize() {
            local_actor::initialize();
            attach(new write(actions));
            attach(new add_write(actions));
        }

    }
}
