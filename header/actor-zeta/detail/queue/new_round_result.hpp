#pragma once

#include <type_traits>

namespace actor_zeta { namespace detail {

    /// Returns the state of a consumer from `new_round`.
    struct new_round_result {
        size_t consumed_items;
        bool stop_all;
    };

    constexpr bool operator==(new_round_result x, new_round_result y) {
        return x.consumed_items == y.consumed_items && x.stop_all == y.stop_all;
    }

    constexpr bool operator!=(new_round_result x, new_round_result y) {
        return !(x == y);
    }

    template <class Inspector>
    bool inspect(Inspector& f, new_round_result& x) {
        return f.object(x).fields(f.field("consumed_items", x.consumed_items),
                                  f.field("stop_all", x.stop_all));
    }

}} // namespace actor_zeta::detail
