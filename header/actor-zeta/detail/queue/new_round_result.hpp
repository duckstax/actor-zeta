#pragma once

namespace actor_zeta { namespace detail {

    struct new_round_result {
        size_t consumed_items;
        bool stop_all;
    };

    constexpr auto operator==(new_round_result x, new_round_result y) -> bool {
        return x.consumed_items == y.consumed_items && x.stop_all == y.stop_all;
    }

    constexpr auto operator!=(new_round_result x, new_round_result y) -> bool {
        return !(x == y);
    }

}} // namespace actor_zeta::detail
