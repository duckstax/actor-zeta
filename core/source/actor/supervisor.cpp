#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message_header.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/supervisor.hpp>

namespace actor_zeta { namespace actor {

        supervisor::supervisor(detail::string_view name):message_passing_interface(name,abstract::supervisor){}

        supervisor::~supervisor() {}

}}