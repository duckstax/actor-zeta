#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <stack>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta { namespace behavior {

  struct context_t {

    virtual ~context_t() = default;

    virtual void address(actor::actor_address)                        = 0;

    virtual auto address(const std::string&) -> actor::actor_address& = 0;

    virtual auto channel(channel::channel) -> void                    = 0;

    virtual auto channel(const std::string&) -> channel::channel&     = 0;

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

#endif //CONTEXT_HPP
