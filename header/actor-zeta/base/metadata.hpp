#pragma once

#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta {

    using actor_id = std::size_t;

    enum class sub_type_t : uint8_t {
        non = 0x00,
        actor,
        supervisor
    };

    struct metadata final {
        actor_id id_;
        sub_type_t sub_type_;
        detail::string_view type_;
    };

} // namespace actor_zeta
