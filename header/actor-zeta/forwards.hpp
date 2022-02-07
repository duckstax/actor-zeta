#pragma once

#include <memory>

namespace actor_zeta {

    namespace base {
        class message;
        class rtt_message;
        using message_ptr = std::unique_ptr<message>;
        using rtt_message_ptr = std::unique_ptr<rtt_message>;
        class actor_abstract;
        class actor;
        class address_t;
        class handler;
        class supervisor_abstract;
        class supervisor;
        class communication_module;
        class cooperative_actor;
    } // namespace base

    namespace scheduler {
        class execution_unit;
    }

} // namespace actor_zeta
