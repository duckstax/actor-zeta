#include <actor-zeta/environment/environment.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>

namespace actor_zeta {
    namespace environment {

        auto environment::operator->() noexcept -> abstract_environment * {
            return environment_.get();
        }

        environment::operator bool() const noexcept {
            return static_cast<bool>(environment_);
        }

        bool environment::operator!() const noexcept {
            return !environment_;
        }

        void environment::swap(environment &env) noexcept {
            using std::swap;
            environment_.swap(env.environment_);
        }

        environment::~environment() {
            if (environment_.get() != nullptr) {
                environment_.release();
            }
        }

        environment::environment(abstract_environment *ptr) : environment_(ptr) {}


    }
}