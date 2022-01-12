#pragma once

#include <string>

namespace actor_zeta { namespace detail {
    /// Communicates the state of a LIFO or FIFO inbox after pushing to it.
    enum class inbox_result {
        /// Indicates that the enqueue operation succeeded and
        /// the reader is ready to receive the data.
        success,

        /// Indicates that the enqueue operation succeeded and
        /// the reader is currently blocked, i.e., needs to be re-scheduled.
        unblocked_reader,

        /// Indicates that the enqueue operation failed because the
        /// queue has been closed by the reader.
        queue_closed,
    };
}} // namespace actor_zeta::detail
