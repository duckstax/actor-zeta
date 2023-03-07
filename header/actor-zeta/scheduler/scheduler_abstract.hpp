#pragma once

#include <atomic>
#include <chrono>
#include <cstddef>

#include <actor-zeta/scheduler/forwards.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>
#include <actor-zeta/scheduler/resumable.hpp>

namespace actor_zeta { namespace scheduler {

    /**
     * @class scheduler_abstract_t
     * @brief
     *
     */
    class scheduler_abstract_t {
    public:
        scheduler_abstract_t(
            std::size_t num_worker_threads,
            std::size_t max_throughput);

        virtual ~scheduler_abstract_t() = default;
        virtual void enqueue(resumable*) = 0;

        inline size_t max_throughput() const {
            return max_throughput_;
        }

        inline size_t num_workers() const {
            return num_workers_;
        }

        virtual void start() = 0;
        virtual void stop() = 0;

    protected:
        std::atomic<size_t> next_worker_;
        size_t max_throughput_;
        size_t num_workers_;
    };

    /**
     * @class cleaner_t
     * @brief
     *
     * @tparam actor_traits
     */
    template<class actor_traits>
    class cleaner_t final {
        actor_zeta::detail::pmr::memory_resource* mr_;

        class dummy_unit final : public execution_unit {
        public:
            dummy_unit(actor_zeta::detail::pmr::memory_resource* mr)
                : execution_unit()
                , resumables(mr) {}

            void execute_later(resumable* job) override {
                resumables.push_back(job);
            }

            typename actor_traits::template vector_type<resumable*> resumables;
        };

    public:
        cleaner_t(actor_zeta::detail::pmr::memory_resource* mr)
            : mr_(mr ? mr : actor_zeta::detail::pmr::get_default_resource()) {}
        ~cleaner_t() = default;

        inline void cleanup_and_release(resumable* ptr) {
            dummy_unit dummy{mr_};
            while (!dummy.resumables.empty()) {
                auto sub = dummy.resumables.back();
                dummy.resumables.pop_back();
            }

            intrusive_ptr_release(ptr);
        }
    };

}} // namespace actor_zeta::scheduler
