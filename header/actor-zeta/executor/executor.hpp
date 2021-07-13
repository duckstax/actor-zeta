#pragma once

#include <condition_variable>
#include <limits>
#include <memory>
#include <set>
#include <thread>
#include <vector>

#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/executor/worker.hpp>

namespace actor_zeta { namespace executor {
    /// @brief
    /// @tparam Policy
    ///
    template<class Policy>
    class executor_t : public abstract_executor {
    public:
        using job_ptr = executable*;
        using policy_data = typename Policy::coordinator_data;
        using worker_type = worker<Policy>;

        executor_t(size_t num_worker_threads, size_t max_throughput_param)
            : abstract_executor(num_worker_threads, max_throughput_param)
            , data_(this) {
        }

        worker_type* worker_by_id(size_t x) {
            return workers_[x].get();
        }

        void execute(job_ptr job) override {
            policy_.central_enqueue(this, job);
        }

        policy_data& data() {
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

            for (auto& w : workers_) {
                w->start();
            }
        }

        void stop() override {
            /// shutdown workers
            class shutdown_helper final
                : public executable
                , public ref_counted {
            public:
                auto run(execution_device* ptr, size_t) -> executable_result override {
                    assert(ptr != nullptr);
                    {
                        std::unique_lock<std::mutex> guard(mtx);
                        last_worker = ptr;
                        cv.notify_all();
                        return executable_result::shutdown;
                    }
                }

                void intrusive_ptr_add_ref_impl() override {
                    intrusive_ptr_add_ref(this);
                }

                void intrusive_ptr_release_impl() override {
                    intrusive_ptr_release(this);
                }

                shutdown_helper()
                    : last_worker(nullptr) {}

                std::mutex mtx;
                std::condition_variable cv;
                execution_device* last_worker;
            };

            shutdown_helper sh;

            std::set<worker_type*> alive_workers;

            auto num = num_workers();

            for (size_t i = 0; i < num; ++i) {
                alive_workers.insert(worker_by_id(i));
                sh.ref();
            }

            while (!alive_workers.empty()) {
                (*alive_workers.begin())->external_enqueue(&sh);

                { /// lifetime scope of guard
                    std::unique_lock<std::mutex> guard(sh.mtx);
                    sh.cv.wait(guard, [&] { return sh.last_worker != nullptr; });
                }

                alive_workers.erase(static_cast<worker_type*>(sh.last_worker));
                sh.last_worker = nullptr;
            }

            for (auto& w : workers_) {
                w->get_thread().join(); /// wait until all workers finish working
            }

            /// run cleanup code for each resumable
            auto f = cleanup_and_release;
            for (auto& w : workers_)
                policy_.foreach_resumable(w.get(), f);
            policy_.foreach_central_resumable(this, f);
        }

    private:
        std::vector<std::unique_ptr<worker_type>> workers_;
        policy_data data_;
        Policy policy_;
    };
}} // namespace actor_zeta::executor
