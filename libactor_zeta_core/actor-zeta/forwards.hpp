#ifndef FORWARDS_HPP
#define FORWARDS_HPP

#include <memory>
#include <cstdint>

namespace actor_zeta {
    namespace messaging {
        class message;
    }

// classes
    class abstract_actor;

    class actor;

    class actor_address;

    class book_contacts;

    class group;

    class cooperation;

    struct abstract_coordinator;

    template<class Policy>
    class coordinator;

//struct
    struct executor_service;
    struct executable;
}

#endif // FORWARDS_HPP
