#ifndef ABSTRACT_COORDINATOR_HPP
#define ABSTRACT_COORDINATOR_HPP

#include <thread>

#include "time_unit.hpp"
#include "actor-zeta/forwards.hpp"
namespace actor_zeta {
    namespace executor {
///
/// @brief abstract concept of an coordination approach
///
        class abstract_coordinator {
        public:
            virtual void submit(executable *) = 0;

            virtual void start() = 0;

            virtual ~abstract_coordinator() = default;

            explicit abstract_coordinator(size_t num_worker_threads, size_t max_throughput_param)
                    : max_throughput_(max_throughput_param),
                      num_workers_(((0 == num_worker_threads) ? std::thread::hardware_concurrency() * 2 - 1 : num_worker_threads)) {
            };

            inline size_t max_throughput() const {
                return max_throughput_;
            }

            inline size_t num_workers() const {
                return num_workers_;
            }

        private:
            size_t max_throughput_;

            size_t num_workers_;
        };
    }
}

#endif // ABSTRACT_COORDINATOR_HPP
