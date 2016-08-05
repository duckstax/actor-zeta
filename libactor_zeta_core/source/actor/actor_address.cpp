#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace actor {
        actor_address::~actor_address() {}

        bool actor_address::is_remote() const noexcept {
            return ptr_->remote();
        }
    }
}
