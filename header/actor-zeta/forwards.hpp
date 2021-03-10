#pragma once

#include <cstddef>

namespace actor_zeta {

    using max_throughput_t = std::size_t;

    namespace base {
        class message;
        class abstract_actor;
        class actor;
        class actor_address;
        class handler;
        class supervisor_t;
        class communication_module;
        class dispatcher_t;
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
