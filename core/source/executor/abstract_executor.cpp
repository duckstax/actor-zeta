#include <actor-zeta/executor/abstract_executor.hpp>


namespace actor_zeta { namespace executor {

        abstract_executor::abstract_executor(
                std::size_t num_worker_threads,
                std::size_t max_throughput
        ):
            next_worker_(0),
            max_throughput_(max_throughput),
            num_workers_(num_worker_threads){

        }

}}
