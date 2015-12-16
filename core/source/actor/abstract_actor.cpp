#include "actor/abstract_actor.hpp"
#include "actor/actor_address.hpp"

namespace actor_model {

    abstract_actor::abstract_actor(std::string type, abstract_coordinator_ptr e) : actor_type(type), _executor(e) { }

    std::string abstract_actor::type() const {
        return actor_type;
    }

    abstract_actor::~abstract_actor() {
        if (_executor != nullptr) {
            _executor = nullptr;
        }
    }

    bool abstract_actor::is_remote() const noexcept {
        return remote;
    };

    actor_address abstract_actor::adddres() const noexcept {
        return actor_address{const_cast<abstract_actor *>(this)};
    }

    void abstract_actor::is_remote(bool r) noexcept {
        remote = r;
    };

    bool abstract_actor::is_blocked() const noexcept {
        return blocked;
    }

    void abstract_actor::is_blocked(bool blocked) noexcept {
        abstract_actor::blocked = blocked;
    }

    bool abstract_actor::is_master() const noexcept {
        return master;
    }

    void abstract_actor::is_master(bool master) noexcept {
        abstract_actor::master = master;
    }
}