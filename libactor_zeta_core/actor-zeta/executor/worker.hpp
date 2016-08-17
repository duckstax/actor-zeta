#ifndef WORKER_HPP
#define WORKER_HPP

#include <thread>
#include <atomic>
#include <mutex>

#include "execution_device.hpp"
#include "executable.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace executor {
        template<class Policy>
        class worker : public execution_device {
        public:
            using job_ptr = executable *;
            using coordinator_ptr = coordinator<Policy> *;
            using policy_data = typename Policy::worker_data;

            worker(size_t worker_id, coordinator_ptr worker_parent, size_t throughput)
                    : max_throughput_(throughput),
                      id_(worker_id),
                      parent_(worker_parent),
                      data_(worker_parent) {
            }

            void start() {
                this_thread_ = std::thread(&worker::run,this);
            }

            worker(const worker &) = delete;

            worker &operator=(const worker &) = delete;

            void external_enqueue(job_ptr job) {
                policy_.external_enqueue(this, job);
            }

            void put_execute_latest(job_ptr job) override {
                policy_.internal_enqueue(this, job);
            }

            coordinator_ptr parent() {
                return parent_;
            }

            size_t id() const {
                return id_;
            }

            policy_data &data() {
                return data_;
            }

            size_t max_throughput() {
                return max_throughput_;
            }

        private:

            void run() {
                for (;;) {
                    auto job = policy_.dequeue(this);
                    auto res = job->run(this, max_throughput_);
                    switch (res) {
                        case executable::executable_result::resume: {
                            policy_.resume_job_later(this, job);
                            break;
                        }
                        case executable::executable_result::done: {
                            //intrusive_ptr_release(job); //TODO : ?
                            break;
                        }
                        case executable::executable_result::awaiting: {
                            //intrusive_ptr_release(job); //TODO : ?
                            break;
                        }
                        case executable::executable_result::shutdown: {
                            return;
                        }
                    }
                }
            }

            size_t max_throughput_;
            std::thread this_thread_;
            size_t id_;
            coordinator_ptr parent_;
            policy_data data_;
            Policy policy_;
        };
    }
}

#endif //WORKER_HPP
