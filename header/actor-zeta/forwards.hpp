#pragma once

namespace actor_zeta {

        class message;

        class abstract_actor;
        class actor;
        class address_t;
        class supervisor;
        class abstract_supervisor;
        class communication_module;
        class cooperative_actor;

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
