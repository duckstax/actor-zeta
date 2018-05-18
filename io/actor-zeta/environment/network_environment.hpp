#ifndef ACTOR_ZETA_NETWORK_ENVIRONMENT_HP
#define ACTOR_ZETA_NETWORK_ENVIRONMENT_HP

#include <actor-zeta/environment/abstract_environment.hpp>
#include <actor-zeta/environment/cooperation.hpp>
#include <actor-zeta/network/multiplexer.hpp>
#include <memory>

namespace actor_zeta { namespace environment {


        using actor_zeta::network::multiplexer;
        using actor_zeta::environment::cooperation;
        using actor_zeta::executor::abstract_coordinator;


        class network_environment final :
                public abstract_environment {
        public:
            network_environment() = delete;

            network_environment(const network_environment &) = delete;

            network_environment &operator=(const network_environment &) = delete;

            ~network_environment() = default;

            network_environment(abstract_coordinator *coordinator, multiplexer *ptr) :
                    multiplexer_(ptr),
                    coordinator_(coordinator) {

            }

            int start() override final {
                coordinator_->start();
                multiplexer_->start();
            }

            executor::abstract_coordinator &manager_execution_device() override final {
                return *coordinator_.get();
            }

            cooperation &manager_group() override final {
                return cooperation_;
            }


        private:
            intrusive_ptr<multiplexer> multiplexer_;
            cooperation cooperation_;
            std::unique_ptr<abstract_coordinator> coordinator_;
        };

    }
}
#endif //ACTOR_ZETA_NETWORK_ENVIRONMENT_HP
