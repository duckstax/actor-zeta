#include "actor/actor_address.hpp"

namespace actor_model {

    actor_address::~actor_address() { }

    bool actor_address::is_remote() const noexcept {
        return ptr_->is_remote();
    }
}
