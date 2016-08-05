#ifndef FORWARDS_HPP
#define FORWARDS_HPP

namespace actor_zeta {

    namespace messaging {
        class message;
    }

    namespace actor {
        class abstract_actor;
        class actor;
        class actor_address;
    }

    namespace behavior{
        class interface_action;
    }

    namespace contacts {
        class book_contacts;
        class group_contacts;
    }

    namespace environment {
        class group;
        class cooperation;
        class environment;
    }

    namespace executor {
        struct abstract_coordinator;
        template<class Policy>
        class coordinator;
        struct execution_device;
        struct executable;
    }
}

#endif // FORWARDS_HPP
