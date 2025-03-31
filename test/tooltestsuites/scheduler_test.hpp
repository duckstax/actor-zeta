#pragma once

#include <deque>

#include "actor-zeta/scheduler/scheduler.hpp"
#include "clock_test.hpp"

namespace actor_zeta { namespace test {

    class scheduler_test_t final : public scheduler::scheduler_t {
    public:
        scheduler_test_t(std::size_t num_worker_threads, std::size_t max_throughput);

        std::deque<scheduler::resumable_t*> jobs;

        bool run_once();
        size_t run(size_t max_count = std::numeric_limits<size_t>::max());
        size_t advance_time(clock::clock_t::duration_type);
        clock_test& clock() noexcept;

    ///protected:
        void start() override;
        void stop() override;
        void schedule(scheduler::resumable_t* ptr) override;

    private:
        clock_test clock_;
    };

}} // namespace actor_zeta::test
