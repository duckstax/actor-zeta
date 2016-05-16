#ifndef WORKER_HPP
#define WORKER_HPP

#include <thread>
#include <atomic>

#include "executor_service.hpp"
#include <mutex>
#include "executable.hpp"
#include "../forwards.hpp"

namespace actor_zeta {
    template<class Policy>
    class worker final : public executor_service {
    public:
        using job_ptr=executable *;
        using policy_data = typename Policy::worker_data;
        using coordinator_ptr = coordinator<Policy> *;

        void external_enqueue(job_ptr job) {
            policy_.external_enqueue(this, job);
        }

        void put_execute_latest(job_ptr job) override {
            policy_.internal_enqueue(this, job);
        }

        policy_data &data() {
            return data_;
        }

        coordinator_ptr parent() {
            return parent_;
        }

        void start() {
            enable = true;
            thread = std::move(std::thread(&worker::run, this));
        }

        worker(const worker &) = delete;

        worker &operator=(const worker &) = delete;

        worker(coordinator_ptr worker_parent, size_t throughput)
                : parent_(worker_parent),max_throughput_(throughput) { }

        void shutdown() override {
            enable = false;
            thread.join();
        }

        const bool is_shutdown() const override {
            return enable;
        }

    private:

        void run() {
            while (enable) {
                auto job = policy_.dequeue(this);
                execute(job);
            }
        }

        void execute(job_ptr job) override {
            switch (job->run(max_throughput_)) {
                case executable::state::done:
                    break;
                case executable::resume:
                    break;
                case executable::waiting:
                    break;
                case executable::shutdown:
                    break;
            }
        }

        std::atomic_bool enable;
        std::thread thread;
        // pointer to central coordinator
        coordinator_ptr parent_;
        // policy-specific data
        policy_data data_;
        // instance of our policy object
        Policy policy_;
        // number of messages each actor is allowed to consume per resume
        size_t max_throughput_;
    };
}

#endif //WORKER_HPP
