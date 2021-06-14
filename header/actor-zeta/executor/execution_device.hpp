#pragma once

#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace executor {
    ///
    /// @brief
    ///
    struct execution_device {
        execution_device() = default;

        execution_device(execution_device&&) = delete;

        execution_device(const execution_device&) = delete;

        virtual ~execution_device();

        virtual void execute(executable*) = 0;
    };
}} // namespace actor_zeta::executor
