#pragma once

#include "forwards.hpp"

namespace actor_zeta { namespace scheduler {

    struct execution_unit {
        execution_unit();
        execution_unit(execution_unit&&) = default;
        execution_unit& operator=(execution_unit&&) = default;
        execution_unit(const execution_unit&) = default;
        execution_unit& operator=(const execution_unit&) = default;
        virtual ~execution_unit();
        virtual void execute_later(resumable* ptr) = 0;
    };

}} // namespace actor_zeta::scheduler
