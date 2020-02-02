#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace base {

///
/// @brief
///

  struct context {

    virtual ~context() = default;

    virtual auto addresses(detail::string_view) -> actor_address&  = 0;

    virtual auto self() -> actor_address                           = 0;

    virtual auto current_message() -> messaging::message&          = 0;

  };

} // namespace behavior
} // namespace actor_zeta
