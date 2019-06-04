#pragma once

#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/actor/async_actor.hpp>

namespace actor_zeta { namespace executor {

    template <class>
    class profiled_executor;

    template<class Policy>
    struct profiled : Policy {
        using executor_type = profiled_executor<profiled<Policy>>;

        static actor_id id_of(executable *job) {
            auto ptr = static_cast<actor::async_actor *>(job);
            return ptr != nullptr ? /*ptr->*/ 1 : 0;
        }

        template<class Worker>
        void before_resume(Worker *worker, executable *job) {
            Policy::before_resume(worker, job);
            auto parent = static_cast<executor_type *>(worker->parent());
            parent->start_measuring(worker->id(), id_of(job));
        }

        template<class Worker>
        void after_resume(Worker *worker, executable *job) {
            Policy::after_resume(worker, job);
            auto parent = static_cast<executor_type *>(worker->parent());
            parent->stop_measuring(worker->id(), id_of(job));
        }

        template<class Worker>
        void after_completion(Worker *worker, executable *job) {
            Policy::after_completion(worker, job);
            auto parent = static_cast<executor_type *>(worker->parent());
            parent->remove_job(id_of(job));
        }
    };

}}