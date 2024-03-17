#pragma once
#include <actor-zeta/scheduler/scheduler_abstract.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <memory>
#include <thread>

#include <actor-zeta/scheduler/execution_unit.hpp>
#include <actor-zeta/scheduler/resumable.hpp>

namespace actor_zeta { namespace scheduler {

    scheduler_abstract_t::scheduler_abstract_t(
        std::size_t num_worker_threads,
        std::size_t max_throughput)
        : next_worker_(0)
        , max_throughput_(max_throughput)
        , num_workers_(num_worker_threads) {
    }

    void cleanup_and_release(resumable* ptr) {
        class dummy_unit : public execution_unit {
        public:
            dummy_unit()
                : execution_unit() {}
            void execute_later(resumable* job) override {
                resumables.push_back(job);
            }
            std::vector<resumable*> resumables;
        };

        dummy_unit dummy{};
        while (!dummy.resumables.empty()) {
            /* ??? auto sub =  ??? */ dummy.resumables.back();
            dummy.resumables.pop_back();
        }

        intrusive_ptr_release(ptr);
    }

}} // namespace actor_zeta::scheduler
