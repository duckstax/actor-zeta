#pragma once

#include <cassert>
#include <cstddef>
#include <thread>

#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/executor/execution_device.hpp>

namespace actor_zeta { namespace executor {

    template<class Policy>
    class executor_t;
    ///
    /// @brief
    /// @tparam Policy
    ///
    template<class Policy>
    class worker final : public execution_device {
    public:
        using job_ptr = executable*;
        using executor_ptr = executor_t<Policy>*;
        using policy_data = typename Policy::worker_data;

        worker(size_t worker_id, executor_ptr worker_parent,
               const policy_data& init, size_t throughput)
            : execution_device()
            , max_throughput_(throughput)
            , id_(worker_id)
            , parent_(worker_parent)
            , data_(init) {
        }

        void start() {
            ///assert(this_thread_.get_id() == std::thread::id{}); TODO: do not check; see implement asio
            auto current_worker = this;
            this_thread_ = std::thread{
                [current_worker] {
                    /// TODO: hook
                    current_worker->run();
                    /// TODO: hook
                }};
        }

        worker(const worker&) = delete;

        worker& operator=(const worker&) = delete;

        void external_enqueue(job_ptr job) {
            assert(job != nullptr); /// TODO: do not check
            policy_.external_enqueue(this, job);
        }

        void execute(job_ptr job) override {
            assert(job != nullptr); /// TODO: do not check
            policy_.internal_enqueue(this, job);
        }

        executor_ptr parent() {
            return parent_;
        }

        size_t id() const {
            return id_;
        }

        std::thread& get_thread() {
            return this_thread_;
        }

        policy_data& data() {
            return data_;
        }

        size_t max_throughput() {
            return max_throughput_;
        }

    private:
        void run() {
            for (;;) {
                auto job = policy_.dequeue(this);
                assert(job != nullptr); /// TODO: do not check
                policy_.before_resume(this, job);
                auto res = job->run(this, max_throughput_);
                policy_.after_resume(this, job);
                switch (res) {
                    case executable_result::resume: {
                        policy_.resume_job_later(this, job);
                        break;
                    }
                    case executable_result::done: {
                        policy_.after_completion(this, job);
                        intrusive_ptr_release(job);
                        break;
                    }
                    case executable_result::awaiting: {
                        intrusive_ptr_release(job);
                        break;
                    }
                    case executable_result::shutdown: {
                        policy_.after_completion(this, job);
                        policy_.before_shutdown(this);
                        return;
                    }
                }
            }
        }

        size_t max_throughput_;
        std::thread this_thread_;
        size_t id_;
        executor_ptr parent_;
        policy_data data_;
        Policy policy_;
    };

}} // namespace actor_zeta::executor
