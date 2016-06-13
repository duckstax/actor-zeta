#include "actor-zeta/broker.hpp"
#include "actor-zeta/standard_handlers/write.hpp"
#include "actor-zeta/standard_handlers/reg_write.hpp"

namespace actor_zeta {
    namespace network {

        broker::broker(const std::string &name) : local_actor(name, nullptr) {
            life.insert("write",new write(actions));
            life.insert("reg_write",new reg_write(actions));
        }
    }
}
