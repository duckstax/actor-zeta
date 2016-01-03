#ifndef WORK_SHARING_HPP
#define WORK_SHARING_HPP

#include <list>
#include <mutex>
#include <cstddef>
#include <condition_variable>
#include "../executable.hpp"

namespace actor_zeta {

// scheduler_policy
    struct work_sharing {
        using job_ptr=executable *;
        // A thead-safe queue implementation.
        using queue_type = std::list<executable *>;

        struct coordinator_data {
            queue_type queue;
            std::mutex lock;
            std::condition_variable cv;
            std::atomic_bool enable;

            inline coordinator_data() {
                // nop
            }
        };

        struct worker_data {
            inline worker_data() {
                // nop
            }
        };

        // Convenience function to access the data field.
        template<class WorkerOrCoordinator>
        static auto d(WorkerOrCoordinator *self) -> decltype(self->data()) {
            return self->data();
        }

        template<class Coordinator>
        void enqueue(Coordinator *self, job_ptr job) {
            queue_type l;
            l.push_back(job);
            std::unique_lock<std::mutex> guard(d(self).lock);
            d(self).queue.splice(d(self).queue.end(), l);
            d(self).cv.notify_one();
        }

        template<class Coordinator>
        void central_enqueue(Coordinator *self, job_ptr job) {
            enqueue(self, job);
        }

        template<class Worker>
        void external_enqueue(Worker *self, job_ptr job) {
            enqueue(self->parent(), job);
        }

        template<class Worker>
        void internal_enqueue(Worker *self, job_ptr job) {
            auto &parent_data = d(self->parent());
            queue_type l;
            l.push_back(job);
            std::unique_lock<std::mutex> guard(parent_data.lock);
            parent_data.queue.splice(parent_data.queue.begin(), l);
            parent_data.cv.notify_one();
        }

        template<class Worker>
        job_ptr dequeue(Worker *self) {
            auto &parent_data = d(self->parent());
            std::unique_lock<std::mutex> guard(parent_data.lock);
            while (parent_data.queue.empty()) {
                parent_data.cv.wait(guard);
            }
            job_ptr job = parent_data.queue.front();
            parent_data.queue.pop_front();
            return job;
        }
    };
}

#endif // WORK_SHARING_HPP
