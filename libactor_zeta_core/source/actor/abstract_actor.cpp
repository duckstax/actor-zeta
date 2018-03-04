#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace actor {
        abstract_actor::abstract_actor(environment::abstract_environment *env, const std::string &type)
                : name_(type),
                  env_(env) {

        }

        const std::string& abstract_actor::type() const {
            return name_;
        }

        actor_address abstract_actor::address() const noexcept {
            return actor_address{const_cast<abstract_actor *>(this)};
        }

        environment::environment & abstract_actor::env() {
            return env_;
        }
    }
}