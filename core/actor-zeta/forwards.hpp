#pragma once

namespace actor_zeta {

    namespace messaging {
        class message;
    }

    namespace actor {
        class  abstract_actor;
        class  actor;
        class  actor_address;
        class  handler;
        class  context;
        struct context_t;
        class supervisor;
    }

    namespace environment {
        class  environment;
        class abstract_environment;
    }

    namespace executor {
        class abstract_executor;
        template<class Policy>
        class  executor;
        struct execution_device;
        struct executable;
    }
}
