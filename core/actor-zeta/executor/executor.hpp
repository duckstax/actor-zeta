#pragma once

#include <thread>
#include <limits>
#include <memory>
#include <condition_variable>
#include <set>
#include <vector>

#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/worker.hpp>

namespace actor_zeta { namespace executor {
/// @brief
/// @tparam Policy
///
        template<class Policy>
        class executor final : public abstract_executor {
        public:
            using job_ptr     = executable *;
            using policy_data = typename Policy::coordinator_data;
            using worker_type = worker<Policy>;

            executor(size_t num_worker_threads, size_t max_throughput_param):
                abstract_executor(num_worker_threads, max_throughput_param),
                data_(this) {
            }

            worker_type *worker_by_id(size_t x) {
                return workers_[x].get();
            }

            void execute(job_ptr job) override {
                policy_.central_enqueue(this, job);
            }

            policy_data &data() {
                return data_;
            }

        protected:
            void start() override {
                typename worker_type::policy_data init{this};
                auto num = num_workers();
                workers_.reserve(num);

                for (size_t i = 0; i < num; ++i) {
                    workers_.emplace_back(new worker_type(i, this, init, max_throughput_));
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
}}
