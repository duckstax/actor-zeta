#pragma once

#include <memory>
#include <stack>

#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief
///

  struct context_t {

    virtual ~context_t() = default;

    virtual auto addresses(detail::string_view) -> actor_address&  = 0;

    virtual auto self() -> actor_address                           = 0;

  };
  

  class context final {
  public:

    context() = default;

    context(context_t* ptr, messaging::message&&);

    ~context();

    messaging::message& message();

    const messaging::message& message() const;

    auto operator ->() noexcept -> context_t*;

    auto operator ->() const noexcept -> context_t*;

    auto operator *() noexcept -> context_t&;

    auto operator *() const noexcept -> context_t&;

  private:
    std::unique_ptr<context_t> ptr;
    messaging::message msg;
  };



} // namespace behavior
} // namespace actor_zeta
