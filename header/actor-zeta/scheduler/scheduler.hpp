#pragma once

#include <atomic>
#include <cstddef>

#include "forwards.hpp"

namespace actor_zeta { namespace scheduler {

    class scheduler_t {
    public:
        virtual ~scheduler_t() = default;
        virtual void schedule(resumable_t*) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;

    };

}} // namespace actor_zeta::scheduler
