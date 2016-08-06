#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace actor {
        abstract_actor::abstract_actor(environment::environment &env, const std::string &type)
                : type_(type), env(env) {}

        const std::string& abstract_actor::type() const {
            return type_;
        }

        bool abstract_actor::remote() const noexcept {
            return remote_;
        };

        actor_address abstract_actor::address() const noexcept {
            return actor_address{const_cast<abstract_actor *>(this)};
        }

        void abstract_actor::remote(bool remote) noexcept {
            this->remote_ = remote;
        };

        bool abstract_actor::blocked() const noexcept {
            return blocked_;
        }

        void abstract_actor::blocked(bool blocked) noexcept {
            this->blocked_ = blocked;
        }

        bool abstract_actor::master() const noexcept {
            return master_;
        }

        void abstract_actor::master(bool master) noexcept {
            this->master_ = master;
        }
    }
}