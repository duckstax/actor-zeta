#pragma once

#include <actor-zeta/environment/abstract_environment.hpp>
#include <actor-zeta/environment/cooperation.hpp>
#include <actor-zeta/network/multiplexer.hpp>
#include <memory>

namespace actor_zeta { namespace environment {


        using actor_zeta::network::multiplexer;
        using actor_zeta::environment::cooperation;
        using actor_zeta::executor::abstract_executor;


        class network_environment final :
                public abstract_environment {
        public:
            network_environment() = delete;

            network_environment(const network_environment &) = delete;

            network_environment &operator=(const network_environment &) = delete;

            ~network_environment() override = default;

            network_environment(abstract_executor *executor_, multiplexer *ptr) :
                    multiplexer_(ptr),
                    executor_(executor_) {

            }

            int start() final {
                executor_->start();
                multiplexer_->start();
                return 0;
            }

            executor::abstract_executor &get_executor() final {
                return *executor_;
            }

            cooperation &manager_group() final {
                return cooperation_;
            }


        private:
            intrusive_ptr<multiplexer> multiplexer_;
            cooperation cooperation_;
            std::unique_ptr<abstract_executor> executor_;
        };

    }
}
