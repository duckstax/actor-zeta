#pragma once

#include <algorithm>
#include <map>
#include <chrono>

#include <actor-zeta/clock/clock.hpp>

namespace actor_zeta { namespace test {

    using handler = actor_zeta::clock::handler;

    class clock_test final : public clock::clock_t {
    public:
        struct schedule_entry final {
            handler f;
            duration_type period;
        };

        using schedule_map = std::multimap<time_point, schedule_entry>;

        clock_test();
        time_point now() const noexcept override;
        void schedule_periodically(time_point, handler, duration_type) override;
        bool trigger_timeout();
        size_t trigger_timeouts();
        size_t advance_time(duration_type);

    private:
        time_point current_time;
        schedule_map schedule;
        bool try_trigger_once();
    };

}} // namespace actor_zeta::test
