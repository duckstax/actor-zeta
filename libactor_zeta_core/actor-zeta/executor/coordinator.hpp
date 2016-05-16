#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include <memory>
#include <vector>
#include "worker.hpp"
#include "abstract_coordinator.hpp"

namespace actor_zeta {
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
                : abstract_coordinator(num_worker_threads, max_throughput_param) {
            size_t size = ((0 == num_worker_threads) ? std::thread::hardware_concurrency() * 2 - 1
                                                     : num_worker_threads);
            workers_.resize(size);
            for (size_t i = 0; i < size; ++i) {
                auto &ref = workers_[i];
                ref.reset(new worker_type(this, max_throughput_param));
            }
            for (auto &w : workers_) {
                w->start();
            }
        }

        void shutdown() override {
            for (auto &i:workers_)
                i->shutdown();
        }

        executor_service *get() override {
            return workers_[0].get();
        }

    private:
        // usually of size std::thread::hardware_concurrency()
        std::vector<std::unique_ptr<worker_type>> workers_;
        // policy-specific data
        policy_data data_;
        // instance of our policy object
        Policy policy_;
    };
}
#endif //COORDINATOR_HPP
