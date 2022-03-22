#pragma once

#include <memory>

namespace actor_zeta { namespace base {
    class message;
    using message_ptr = std::unique_ptr<message>;
    class actor_abstract;
    class actor;
    class address_t;
    class handler;
    class supervisor_abstract;
    class supervisor;
    class communication_module;
    class cooperative_actor;
}} // namespace actor_zeta::base
