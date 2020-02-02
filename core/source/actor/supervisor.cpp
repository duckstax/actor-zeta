// clang-format off
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/base/supervisor.hpp>
// clang-format on

namespace actor_zeta { namespace base {

        supervisor::supervisor(detail::string_view name): communication_module(name, abstract::supervisor){}

        supervisor::~supervisor() {}

        auto supervisor::current_message() -> messaging::message & {
            return current_message_;
        }

        auto supervisor::set_current_message(messaging::message msg) -> void  {
            current_message_ = std::move(msg);
        }

}}