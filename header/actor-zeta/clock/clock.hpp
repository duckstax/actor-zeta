#pragma once

#include <chrono>
#include <string>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/detail/unique_function.hpp>

namespace actor_zeta { namespace clock {

    using handler = detail::unique_function<void()>;

    class clock_t {
    public:
        using clock_type = std::chrono::steady_clock;
        using time_point = typename clock_type::time_point;
        using duration_type = typename clock_type::duration;

        virtual ~clock_t();
        virtual time_point now() const noexcept;
        void schedule_message(time_point , base::address_t target, base::message_ptr content);

    protected:
        virtual void schedule_periodically(time_point first_run, handler, duration_type period) = 0;
        void schedule(handler );
        void schedule(time_point , handler );
    };

}} // namespace actor_zeta::clock
