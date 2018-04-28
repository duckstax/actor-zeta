#include "actor-zeta/environment/environment.hpp"
#include "actor-zeta/executor/abstract_coordinator.hpp"

namespace actor_zeta {
    namespace environment {

        auto environment::operator->() -> abstract_environment * {
            return environment_.get();
        }

        environment::operator bool() const {
            return static_cast<bool>(environment_);
        }

        bool environment::operator!() const {
            return !environment_;
        }

        void environment::swap(environment &env) {
            using std::swap;
            environment_.swap(env.environment_);
        }

        environment::~environment() {
            if (environment_.get() != nullptr) {
                auto *tmp = environment_.release();
                tmp = nullptr;
            }
        }

        environment::environment(abstract_environment *ptr) : environment_(ptr) {}


    }
}