#ifndef WORK_SHARING_HPP
#define WORK_SHARING_HPP

#include <list>
#include <mutex>
#include <cstddef>
#include <condition_variable>

#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace executor {
///
/// @brief Stands for work sharing approach
///
        class work_sharing {
        private:
            template<class WorkerOrCoordinator>
            static auto cast(WorkerOrCoordinator *self) -> decltype(self->data()) {
                return self->data();
            }

        public:
            using queue_type = std::list<executable *>;

            ~work_sharing() {}
///
/// @brief This structure is used as coordinator data keeper
///
            struct coordinator_data {
                inline explicit coordinator_data(executor::abstract_coordinator *) {
                }

                queue_type queue;
                std::mutex lock;
                std::condition_variable cv;
            };
///
/// @brief This structure is used as worker data keeper
///
            struct worker_data {
                inline explicit worker_data(executor::abstract_coordinator *) {
                }
            };

            template<class Coordinator>
            void enqueue(Coordinator *self, executable *job) {
                queue_type l;
                l.push_back(job);
                std::unique_lock<std::mutex> guard(cast(self).lock);
                cast(self).queue.splice(cast(self).queue.end(), l);
                cast(self).cv.notify_one();
            }

            template<class Coordinator>
            void central_enqueue(Coordinator *self, executable *job) {
                enqueue(self, job);
            }

            template<class Worker>
            void external_enqueue(Worker *self, executable *job) {
                enqueue(self->parent(), job);
            }

            template<class Worker>
            void internal_enqueue(Worker *self, executable *job) {
                enqueue(self->parent(), job);
            }

            template<class Worker>
            void resume_job_later(Worker *self, executable *job) {
                enqueue(self->parent(), job);
            }

            template<class Worker>
            executable *dequeue(Worker *self) {
                auto &parent_data = cast(self->parent());
                std::unique_lock<std::mutex> guard(parent_data.lock);
                parent_data.cv.wait(guard, [&] { return !parent_data.queue.empty(); });
                executable *job = parent_data.queue.front();
                parent_data.queue.pop_front();
                return job;
            }

            template<class Coordinator, class UnaryFunction>
            void foreach_central_resumable(Coordinator *self, UnaryFunction f) {
                auto &queue = cast(self).queue;
                auto next = [&]() -> executable * {
                    if (queue.empty()) {
                        return nullptr;
                    }
                    auto front = queue.front();
                    queue.pop_front();
                    return front;
                };
                std::unique_lock<std::mutex> guard(cast(self).lock);
                for (auto job = next(); job != nullptr; job = next()) {
                    f(job);
                }
            }
        };
    }
}

#endif // WORK_SHARING_HPP
