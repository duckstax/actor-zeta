#pragma once

namespace actor_zeta {

    namespace messaging {
        class message;
        class message_header;
    }

    namespace actor {
        class  abstract_actor;
        class  actor;
        class  actor_address;
        class  handler;
        struct context;
        class supervisor;
        class message_passing_interface;
        class dispatcher_t;
    }

    namespace environment {
        class environment;
        class abstract_environment;
    }

    namespace executor {
        class abstract_executor;
        template<class Policy>
        class  executor_t;
        struct execution_device;
        struct executable;
    }
}
