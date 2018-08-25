#pragma once

namespace actor_zeta {

    namespace messaging {
        class message;
    }

    namespace actor {
        class abstract_actor;
        class actor;
        class actor_address;
    }

    namespace behavior {
        class  abstract_action;
        class  context;
        struct context_t;
        class  fsm;
    }

    namespace channel {
        struct abstract_channel;
        class  channel;
    }

    namespace environment {
        class  group;
        class  cooperation;
        class  environment;
        struct abstract_environment;
    }

    namespace executor {
        class abstract_coordinator;
        template<class Policy>
        class  coordinator;
        struct execution_device;
        struct executable;
    }
}
