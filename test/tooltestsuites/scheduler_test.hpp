#pragma once

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <deque>
#include <functional>
#include <limits>

#include "actor-zeta/base/actor_abstract.hpp"
#include "actor-zeta/scheduler/resumable.hpp"
#include "actor-zeta/scheduler/scheduler_abstract.hpp"

#include "clock_test.hpp"

namespace actor_zeta { namespace test {

    class scheduler_test_t final : public scheduler::scheduler_abstract_t {
    public:
        using super = scheduler::scheduler_abstract_t;

        scheduler_test_t(std::size_t num_worker_threads, std::size_t max_throughput);

        std::deque<scheduler::resumable*> jobs;

        bool run_once();
        size_t run(size_t max_count = std::numeric_limits<size_t>::max());

    protected:
        void start() override;
        void stop() override;
        void enqueue(scheduler::resumable* ptr) override;
    };

}} // namespace actor_zeta::test
