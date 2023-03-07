#pragma once

#include <cassert>
#include <condition_variable>
#include <limits>
#include <memory>
#include <thread>

#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/scheduler/worker.hpp>

namespace actor_zeta { namespace scheduler {

    template<class Policy, class actor_traits>
    class scheduler_t : public scheduler_abstract_t {
        actor_zeta::detail::pmr::memory_resource* mr_;

    public:
        using super = scheduler_abstract_t;
        using policy_data = typename Policy::coordinator_data;
        using worker_type = worker<Policy, actor_traits>;
        using deleter_type = typename actor_traits::template deleter_type<worker_type>;
        using unique_pointer = typename actor_traits::template unique_ptr_type<worker_type>;
        using vector_type = typename actor_traits::template vector_type<unique_pointer>;
        using set_type = typename actor_traits::template set_type<worker_type*>;

        scheduler_t(actor_zeta::detail::pmr::memory_resource* mr, size_t num_worker_threads, size_t max_throughput_param)
            : scheduler_abstract_t(num_worker_threads, max_throughput_param)
            , mr_(mr)
            , workers_(mr)
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
                workers_.emplace_back(
                    unique_pointer{
                        actor_zeta::detail::pmr::allocate_ptr<worker_type>(mr_, i, this, init, max_throughput_),
                        deleter_type(mr_)
                    });
            }

            for (auto& w : workers_) {
                w->start();
            }

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
            set_type alive_workers{mr_};
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
//            auto f = &cleanup_and_release<actor_traits>;
            auto cln = cleaner_t<actor_traits>(mr_);
            auto f = [&cln](resumable* r) {
                cln.cleanup_and_release(r);
            };
            for (auto& w : workers_) {
                policy_.foreach_resumable(w.get(), f);
            }
            policy_.foreach_central_resumable(this, f);
        }

        void enqueue(resumable* ptr) override {
            policy_.central_enqueue(this, ptr);
        }

    private:
        vector_type workers_;
        policy_data data_;
        Policy policy_;
    };

}} // namespace actor_zeta::scheduler