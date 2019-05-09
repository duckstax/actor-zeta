#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta { namespace actor {
        abstract_actor::abstract_actor(environment::abstract_environment *env, const std::string &name):
                env_(env) {

            type_.type = abstract::actor;
            type_.name = name;
        }

        actor_address abstract_actor::address() const noexcept {
            return actor_address{const_cast<abstract_actor *>(this)};
        }

        environment::environment & abstract_actor::env() {
            return env_;
        }

        abstract_actor::~abstract_actor() {

        }

        auto abstract_actor::type() const -> abstract {
            return type_.type;
        }

        auto abstract_actor::name() const -> const std::string & {
            return type_.name;
        }

        auto abstract_actor::locating() const -> locations {
            return type_.location;
        }

        auto abstract_actor::message_types() const -> std::set<std::string> {
            return std::set<std::string>();
        }


    }
}
