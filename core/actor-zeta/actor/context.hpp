#pragma once

#include <memory>
#include <stack>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief
///

  struct context {

    virtual ~context() = default;

    virtual auto addresses(detail::string_view) -> actor_address&  = 0;

    virtual auto self() -> actor_address                           = 0;

    virtual auto message() -> messaging::message& = 0;

  };

} // namespace behavior
} // namespace actor_zeta
