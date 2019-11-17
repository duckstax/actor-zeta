// clang-format off
#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/supervisor.hpp>
// clang-format on

namespace actor_zeta { namespace actor {

        supervisor::supervisor(detail::string_view name): communication_module(name, abstract::supervisor){}

        supervisor::~supervisor() {}

        auto supervisor::current_message() -> messaging::message & {
            return current_message_;
        }

        auto supervisor::set_current_message(messaging::message msg) -> void  {
            current_message_ = std::move(msg);
        }

}}