#pragma once

namespace actor_zeta { namespace detail {

    template<class T>
    struct singly_linked {
        using node_type = singly_linked<T>;
        using node_pointer = node_type*;

        node_pointer next;

        explicit singly_linked(node_pointer n = nullptr)
            : next(n) {}
    };

}} // namespace actor_zeta::detail
