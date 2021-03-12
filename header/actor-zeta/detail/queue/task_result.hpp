#pragma once

namespace actor_zeta { namespace detail {

    /// Communicates the state of a consumer to a task queue.
    enum class task_result {
        /// The consumer processed the task and is ready to receive the next one.
        resume,
        /// The consumer skipped the task and is ready to receive the next one.
        /// Illegal for consumers of non-cached queues (non-cached queues treat
        /// `skip` and `resume` in the same way).
        skip,
        /// The consumer processed the task but does not accept further tasks.
        stop,
        /// The consumer processed the task but does not accept further tasks and no
        /// subsequent queue shall start a new round.
        stop_all,
    };

}} // namespace actor_zeta::detail