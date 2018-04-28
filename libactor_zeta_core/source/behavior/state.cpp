#include <actor-zeta/behavior/state.hpp>
#include <sys/wait.h>

namespace actor_zeta { namespace behavior {

        state_t::state_t(messaging::message &&msg) : msg(std::move(msg)) {

        }

        messaging::message state_t::message() {
            return std::move(msg); /// TODO hack
        }

        const messaging::message &state_t::message() const {
            return msg;
        }

    } /// behavior
} /// actor_zeta

