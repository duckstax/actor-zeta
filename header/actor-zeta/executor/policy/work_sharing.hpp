#pragma once

#include <condition_variable>
#include <cstddef>
#include <list>
#include <mutex>

#include <actor-zeta/executor/policy/unprofiled.hpp>

namespace actor_zeta { namespace executor {
    ///
    /// @brief
    ///
    class work_sharing : public unprofiled {
    public:
        using queue_type = std::list<executable*>;

        ~work_sharing() override;
        ///
        /// @brief
        ///
        struct coordinator_data final {
            inline explicit coordinator_data(abstract_executor*) {}
            queue_type queue;
            std::mutex lock;
            std::condition_variable cv;
        };
        ///
        /// @brief
        ///
        struct worker_data final {
            inline explicit worker_data(abstract_executor*) {}
        };

        template<class Coordinator>
        void enqueue(Coordinator* self, executable* job) {
            queue_type l;
            l.push_back(job);
            std::unique_lock<std::mutex> guard(cast(self).lock);
            cast(self).queue.splice(cast(self).queue.end(), l);
            cast(self).cv.notify_one();
        }

        template<class Coordinator>
        void central_enqueue(Coordinator* self, executable* job) {
            enqueue(self, job);
        }

        template<class Worker>
        void external_enqueue(Worker* self, executable* job) {
            enqueue(self->parent(), job);
        }

        template<class Worker>
        void internal_enqueue(Worker* self, executable* job) {
            enqueue(self->parent(), job);
        }

        template<class Worker>
        void resume_job_later(Worker* self, executable* job) {
            enqueue(self->parent(), job);
        }

        template<class Worker>
        executable* dequeue(Worker* self) {
            auto& parent_data = cast(self->parent());
            std::unique_lock<std::mutex> guard(parent_data.lock);
            parent_data.cv.wait(guard, [&] { return !parent_data.queue.empty(); });
            executable* job = parent_data.queue.front();
            parent_data.queue.pop_front();
            return job;
        }

        template<class Worker, class UnaryFunction>
        void foreach_resumable(Worker*, UnaryFunction) {
        }

        template<class Coordinator, class UnaryFunction>
        void foreach_central_resumable(Coordinator* self, UnaryFunction f) {
            auto& queue = cast(self).queue;
            auto next = [&]() -> executable* {
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

}} // namespace actor_zeta::executor
