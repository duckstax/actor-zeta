#pragma once

namespace actor_zeta {

    namespace messaging {
        class message;
        class message_header;
    }

    namespace base {
        class  abstract_actor;
        class  actor;
        class  actor_address;
        class  handler;
        struct context;
        class supervisor;
        class communication_module;
        class dispatcher_t;
        class cooperative_actor;
    }

    namespace executor {
        class work_sharing;
        template<class T>
        struct profiled;
        template <class>
        class profiled_executor;
        class abstract_executor;
        template<class Policy>
        class  executor_t;
        struct execution_device;
        struct executable;
    }
}
