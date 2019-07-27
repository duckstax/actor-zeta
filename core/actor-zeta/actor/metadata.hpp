#pragma once

#include <string>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta {

        using actor_id = std::size_t;

        enum class abstract : uint8_t {
            non = 0x00,
            actor,
            supervisor
        };

        enum class locations : uint8_t {
            non = 0x00,
            local,
            remote,
        };

        struct metadata final {
            abstract type;
            locations location;
            detail::string_view name;
        };

} /// actor_zeta
