#ifndef FWD_HPP
#define FWD_HPP

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
//using
    using executor_ptr=executor_service *;
    using executable_ptr=executable *;
    using abstract_coordinator_ptr=abstract_coordinator *;
}

#endif // FWD_HPP
