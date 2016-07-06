#include "actor-zeta/broker.hpp"
#include "actor-zeta/standard_handlers/write.hpp"
#include "actor-zeta/standard_handlers/reg_write.hpp"

namespace actor_zeta {
    namespace network {

        broker::broker(const std::string &name) : local_actor(name, nullptr) {
            initialize();
        }

        void broker::initialize() {
            local_actor::initialize();
            life.insert(new write(actions));
            life.insert(new reg_write(actions));
        }

    }
}
