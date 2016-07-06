#include "actor-zeta/actor/actor.hpp"
#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace actor {
        actor::~actor() {}

        actor_address actor::address() const noexcept {
            return heart->adddres();
        };

        bool actor::is_remote() const noexcept {
            return heart->is_remote();
        }

        std::string actor::type() const {
            return heart->type();
        }

        void actor::swap(actor &other) noexcept {
            heart.swap(other.heart);
        }
    }
}