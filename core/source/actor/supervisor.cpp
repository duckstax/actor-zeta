#include <actor-zeta/actor/supervisor.hpp>

namespace actor_zeta { namespace actor {

        supervisor::supervisor(detail::string_view name):message_passing_interface(name,abstract::supervisor){}

        supervisor::~supervisor() {}

}}