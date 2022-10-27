#pragma once

#include <cstdlib>
#include <unistd.h>

namespace actor_zeta { namespace detail {

    enum class task_result : int8_t {
        resume,
        skip,
        stop,
        stop_all,
    };

}} // namespace actor_zeta::detail
