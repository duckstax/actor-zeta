#pragma once

namespace actor_zeta { namespace detail {

    /// Intrusive base for singly linked types that allows queues to use `T` with
    /// dummy nodes.
    template<class T>
    struct singly_linked {
        // -- member types -----------------------------------------------------------

        /// The type for dummy nodes in singly linked lists.
        using node_type = singly_linked<T>;

        /// Type of the pointer connecting two singly linked nodes.
        using node_pointer = node_type*;

        // -- constructors, destructors, and assignment operators --------------------

        singly_linked(node_pointer n = nullptr)
            : next(n) {
            // nop
        }

        // -- member variables -------------------------------------------------------

        /// Intrusive pointer to the next element.
        node_pointer next;
    };

}} // namespace actor_zeta::detail
