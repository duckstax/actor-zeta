#pragma once

namespace actor_zeta { namespace detail {

    enum class task_result : uint8_t {
        resume,
        skip,
        stop,
        stop_all,
    };

}} // namespace actor_zeta::detail
