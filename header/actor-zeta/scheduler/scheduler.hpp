#pragma once

#include <cassert>
#include <condition_variable>
#include <limits>
#include <memory>
#include <set>
#include <thread>
#include <vector>

#include <actor-zeta/clock/thread_safe_clock.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/scheduler/worker.hpp>

namespace actor_zeta { namespace scheduler {

    template<class Policy>
    class scheduler_t : public scheduler_abstract_t {
    public:
        using super = scheduler_abstract_t;
        using policy_data = typename Policy::coordinator_data;
        using worker_type = worker<Policy>;

        scheduler_t(size_t num_worker_threads, size_t max_throughput_param)
            : scheduler_abstract_t(num_worker_threads, max_throughput_param)
            , data_(this) {
        }

        worker_type* worker_by_id(size_t x) {
            return workers_[x].get();
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

            clock_.start_dispatch_loop();
            super::start();
        }

        void stop() override {
            class shutdown_helper
                : public resumable
                , public ref_counted {
            public:
                resume_result resume(execution_unit* ptr, size_t) override {
                    assert(ptr != nullptr);
                    std::unique_lock<std::mutex> guard(mtx);
                    last_worker = ptr;
                    cv.notify_all();
                    return resume_result::shutdown;
                }

                void intrusive_ptr_add_ref_impl() override {
                    intrusive_ptr_add_ref(this);
                }

                void intrusive_ptr_release_impl() override {
                    intrusive_ptr_release(this);
                }

                shutdown_helper(): last_worker(nullptr) {}

                std::mutex mtx;
                std::condition_variable cv;
                execution_unit* last_worker;
            };
            // Use a set to keep track of remaining workers.
            shutdown_helper sh;
            std::set<worker_type*> alive_workers;
            auto num = num_workers();
            for (size_t i = 0; i < num; ++i) {
                alive_workers.insert(worker_by_id(i));
                sh.ref(); // Make sure reference count is high enough.
            }
            while (!alive_workers.empty()) {
                (*alive_workers.begin())->external_enqueue(&sh);
                { // lifetime scope of guard
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
            auto f = &cleanup_and_release;
            for (auto& w : workers_) {
                policy_.foreach_resumable(w.get(), f);
            }
            policy_.foreach_central_resumable(this, f);
            clock_.stop_dispatch_loop();
        }

        void enqueue(resumable* ptr) override {
            policy_.central_enqueue(this, ptr);
        }

        clock::clock_t& clock() noexcept override {
            return clock_;
        }

    private:
        clock::thread_safe_clock_t clock_;
        std::vector<std::unique_ptr<worker_type>> workers_;
        policy_data data_;
        Policy policy_;
        std::thread timer_;
    };

}} // namespace actor_zeta::scheduler