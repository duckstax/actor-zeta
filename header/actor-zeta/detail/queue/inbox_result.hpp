#pragma once

#include <string>

namespace actor_zeta { namespace detail {

    /// Communicates the state of a LIFO or FIFO inbox after pushing to it.
    enum class inbox_result : uint8_t {
        success,
        unblocked_reader,
        queue_closed
    };

}} // namespace actor_zeta::detail
