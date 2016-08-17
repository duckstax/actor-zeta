#include "actor-zeta/broker.hpp"
#include "actor-zeta/standard_handlers/write.hpp"
#include "actor-zeta/standard_handlers/add_write.hpp"
#include "actor-zeta/standard_handlers/remove_write.hpp"

namespace actor_zeta {
    namespace network {

        broker::broker(environment::environment &env,const std::string &name) : scheduled_actor(env, name) {
            initialize();
        }

        void broker::initialize() {
            actor::local_actor::initialize();
            attach(new write(actions));
            attach(new add_write(actions));
            attach(new remove_write(actions));
        }
    }
}
