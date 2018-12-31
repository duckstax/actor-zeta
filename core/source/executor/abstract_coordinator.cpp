#include <actor-zeta/executor/abstract_coordinator.hpp>


namespace actor_zeta { namespace executor {

        abstract_coordinator::abstract_coordinator(
                std::size_t num_worker_threads,
                std::size_t max_throughput
        ):
            next_worker_(0),
            max_throughput_(0),
            num_workers_(0){

        }

}}
