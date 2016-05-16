#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    struct executable {
        enum state {
            resume,
            waiting,
            done,
            shutdown
        };

        virtual ~executable() { }

        virtual void attach_to_scheduler() = 0;

        virtual void detach_from_scheduler() = 0;

        virtual state run(size_t max_throughput) = 0;
    };
}
#endif //EXECUTABLE_HPP
