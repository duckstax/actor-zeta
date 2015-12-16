#ifndef EXECUTOR_SERVICE_HPP
#define EXECUTOR_SERVICE_HPP

#include "time_unit.hpp"
#include "fwd.hpp"

namespace actor_model {
    struct executor_service {
        virtual void execute(executable_ptr) = 0;

        virtual void put_execute_latest(executable_ptr) = 0;

        virtual void shutdown() = 0;

        virtual const bool is_shutdown() const = 0;

/*
        virtual bool is_terminated() = 0;

        virtual bool await_termination(long timeout, TimeUnit unit) = 0;
*/
        virtual ~executor_service() { }
    };
}
#endif //EXECUTOR_SERVICE_HPP
