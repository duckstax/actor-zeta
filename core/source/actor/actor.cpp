#include "actor/actor.hpp"
#include "actor/abstract_actor.hpp"
#include "actor/actor_address.hpp"

namespace actor_model {

    actor::~actor() { }

    actor_address actor::address() const noexcept {
        return heart->adddres();
    };

    inline bool actor::is_remote() const noexcept {
        return heart->is_remote();
    }

    std::string actor::type() const {
        return heart->type();
    }

    void actor::swap(actor &other) noexcept {
        heart.swap(other.heart);
    }
}