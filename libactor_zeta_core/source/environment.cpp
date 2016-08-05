#include "actor-zeta/environment.hpp"

namespace actor_zeta {
    namespace environment {

        environment::environment(executor::abstract_coordinator *ac) : coordinator_(ac) {
        }

        executor::abstract_coordinator &environment::manager_execution_device() {
            return *coordinator_;
        }

        cooperation &environment::manager_group() {
            return cooperation_;
        }
    }
}

