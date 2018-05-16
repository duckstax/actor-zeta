#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta {
    namespace actor {
        actor::~actor() {}

        actor_address actor::address() const noexcept {
            return heart->address();
        };

        const std::string& actor::name() const {
            return heart->name();
        }

        void actor::swap(actor &other) noexcept {
            using std::swap;
            heart.swap(other.heart);
        }
    }
}
