#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include <memory>
#include <vector>

#include "worker.hpp"
#include "abstract_coordinator.hpp"

namespace actor_zeta {
    namespace executor {
        template<class Policy>
        class coordinator final : public abstract_coordinator {
        public:
            using job_ptr=executable *;
            using policy_data = typename Policy::coordinator_data;
            using worker_type=worker<Policy>;

            policy_data &data() {
                return data_;
            }

            worker_type *worker_by_id(size_t id) {
                return workers_[id].get();
            }

            void submit(job_ptr job) override {
                policy_.central_enqueue(this, job);
            }

            coordinator(size_t num_worker_threads, size_t max_throughput_param)
                    : abstract_coordinator(num_worker_threads, max_throughput_param), data_(this) {
            }

            void start() {
                size_t size = num_workers();
                workers_.reserve(num_workers());
                for (size_t i = 0; i < size; ++i) {
                    workers_.emplace_back(new worker_type(i, this, max_throughput()));
                }

                for (auto &w : workers_) {
                    w->start();
                }
            }

        private:
            std::vector<std::unique_ptr<worker_type>> workers_;
            policy_data data_;
            Policy policy_;
        };
    }
}
#endif //COORDINATOR_HPP
