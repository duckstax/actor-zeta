#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <stack>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/behavior/state.hpp>
#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta { namespace behavior {

  struct context_t {

    virtual ~context_t() = default;

    virtual void send_channel(messaging::message &&) const                           = 0;

    virtual void broadcast_channel(messaging::message &&) const                      = 0;

    virtual bool send(messaging::message &&)                                         = 0;

    virtual void address(actor::actor_address)                                       = 0;

    virtual actor::actor_address address(const std::string&)                         = 0;

    virtual void channel(channel::channel)                                           = 0;

    virtual channel::channel channel(const std::string&)                             = 0;

  };
  

  class context final {
  public:

    context() = default;

    context(context_t* ptr, messaging::message&&);

    ~context();

    state_t& state() const;

    state_t* get_state();

    auto operator ->() noexcept -> context_t*;

    auto operator ->() const noexcept -> context_t*;

    auto operator *() noexcept -> context_t&;

    auto operator *() const noexcept -> context_t&;

  private:
    std::unique_ptr<context_t> ptr;
    std::unique_ptr<state_t> current_state;
  };



} // namespace behavior
} // namespace actor_zeta

#endif //CONTEXT_HPP
