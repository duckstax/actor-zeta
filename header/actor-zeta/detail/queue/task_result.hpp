#pragma once

#include <cstdint>

namespace actor_zeta { namespace detail {

    /// Communicates the state of a consumer to a task queue.
    enum class task_result : uint8_t {
        resume,
        skip,
        stop,
        stop_all,
    };

}} // namespace actor_zeta::detail