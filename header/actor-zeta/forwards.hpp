#pragma once

#include <memory>

namespace actor_zeta {

    namespace base {
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
    } // namespace base

    namespace executor {
        class work_sharing;
        template<class T>
        struct profiled;
        template<class>
        class profiled_executor;
        class abstract_executor;
        template<class Policy>
        class executor_t;
        struct execution_device;
        struct executable;
    } // namespace executor
} // namespace actor_zeta
