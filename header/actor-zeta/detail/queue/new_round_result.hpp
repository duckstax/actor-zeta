#pragma once

#include <type_traits>

#include "caf/fwd.hpp"

namespace actor_zeta { namespace detail {

    /// Returns the state of a consumer from `new_round`.
    struct new_round_result {
        /// Denotes whether the consumer accepted at least one element.
        size_t consumed_items;
        /// Denotes whether the consumer returned `task_result::stop_all`.
        bool stop_all;
    };

    constexpr bool operator==(new_round_result x, new_round_result y) {
        return x.consumed_items == y.consumed_items && x.stop_all == y.stop_all;
    }

    constexpr bool operator!=(new_round_result x, new_round_result y) {
        return !(x == y);
    }

}} // namespace actor_zeta::detail
