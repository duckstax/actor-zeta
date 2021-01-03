#pragma once

namespace actor_zeta {

    namespace messaging {
        class message;
        class message_header;
    }

    namespace base {
        class  abstract_actor;
        class  actor;
        class address_type;
        class supervisor;
        class abstract_supervisor;
        class communication_module;
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
