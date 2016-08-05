#ifndef EXECUTOR_SERVICE_HPP
#define EXECUTOR_SERVICE_HPP

#include "time_unit.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace executor {
    struct execution_device {
        execution_device() = default;

        execution_device(execution_device &&) = delete;

        execution_device(const execution_device &) = delete;

        virtual ~execution_device() = default;

        virtual void put_execute_latest(executable *) = 0;

        //virtual void shutdown() = 0;

        //virtual const bool is_shutdown() const = 0;

        //virtual bool is_terminated() = 0;

        //virtual bool await_termination(long timeout, TimeUnit unit) = 0;

    };
}}
#endif //EXECUTOR_SERVICE_HPP
