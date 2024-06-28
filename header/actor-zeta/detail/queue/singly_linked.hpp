#pragma once

namespace actor_zeta { namespace detail {

    template<class T>
    struct singly_linked {
        using node_type = singly_linked<T>;
        using node_pointer = node_type*;
        singly_linked() noexcept = default;
        explicit singly_linked(node_pointer n) noexcept
            : next(n) {}

        /// singly_linked(const singly_linked&) = delete; TODO:  it is necessary to strengthen guarantees
        /// singly_linked& operator=(const singly_linked&) = delete; TODO:  it is necessary to strengthen guarantees
        node_pointer next = nullptr;
    };

}} // namespace actor_zeta::detail
