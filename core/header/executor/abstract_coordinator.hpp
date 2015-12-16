#ifndef ABSTRACT_COORDINATOR_HPP
#define ABSTRACT_COORDINATOR_HPP

#include "time_unit.hpp"
#include "fwd.hpp"

namespace actor_model {
    class abstract_coordinator {
    public:
        virtual void submit(executable *) = 0;

        virtual void shutdown() = 0;

        virtual executor_service *get() = 0;

        virtual ~abstract_coordinator() { }

        explicit abstract_coordinator(size_t num_worker_threads, size_t max_throughput_param)
                : max_throughput_(max_throughput_param), num_workers_(num_worker_threads) { };

        inline size_t max_throughput() const {
            return max_throughput_;
        }

        inline size_t num_workers() const {
            return num_workers_;
        }

    private:
        // number of messages each actor is allowed to consume per resume
        size_t max_throughput_;

        size_t num_workers_;
        /*
        virtual void schedule(runnable_ptr command, long delay, TimeUnit unit) = 0;

        virtual void scheduleAtFixedRate(runnable_ptr command, long initialDelay, long period, TimeUnit unit) = 0;

        virtual void scheduleWithFixedDelay(runnable_ptr command, long initialDelay, long delay, TimeUnit unit) = 0;
        */
    };
}

#endif // ABSTRACT_COORDINATOR_HPP
