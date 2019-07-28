#include <actor-zeta/network_environment.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>

namespace actor_zeta { namespace environment {

        network_environment::network_environment(abstract_executor *executor_, multiplexer *ptr) :
                multiplexer_(ptr),
                executor_(executor_) {
        }

        std::size_t network_environment::start() {
            executor_->start();
            multiplexer_->start();
            return 0;
        }

        executor::abstract_executor &network_environment::get_executor() {
            return *executor_;
        }
    }}