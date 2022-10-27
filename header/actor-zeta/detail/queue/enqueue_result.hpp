#pragma once

#include <cstdlib>
#include <unistd.h>

namespace actor_zeta { namespace detail {

    enum class enqueue_result : int8_t {
        success,
        unblocked_reader,
        queue_closed
    };

}} // namespace actor_zeta::detail
