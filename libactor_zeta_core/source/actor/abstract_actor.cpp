#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace actor {
        abstract_actor::abstract_actor(environment::environment &env, const std::string &type)
                : type_(type), env_(env) {}

        const std::string& abstract_actor::type() const {
            return type_;
        }

        actor_address abstract_actor::address() const noexcept {
            return actor_address{const_cast<abstract_actor *>(this)};
        }

        environment::environment &abstract_actor::env() const {
            return env_;
        }
    }
}