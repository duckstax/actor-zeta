#ifndef FORWARDS_HPP
#define FORWARDS_HPP

namespace actor_zeta {

    namespace messaging {
        class message;
    }

    namespace actor{
        class abstract_actor;
        class actor;
        class actor_address;
    }

    namespace contacts {
        class book_contacts;
        class group_contacts;
    }

    namespace environment {
        class group;
        class cooperation;
    }

    struct abstract_coordinator;

    template<class Policy>
    class coordinator;

    struct executor_service;
    struct executable;
}

#endif // FORWARDS_HPP
