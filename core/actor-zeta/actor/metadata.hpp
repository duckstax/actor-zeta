#pragma once

#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta {

        using actor_id = std::size_t;

        enum class abstract : uint8_t {
            non = 0x00,
            actor,
            supervisor
        };

        struct metadata final {
            actor_id id_;
            abstract type;
            detail::string_view name;
        };

} /// actor_zeta
