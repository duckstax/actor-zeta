#ifndef BLOCKING_MAIL_QUEUE_HPP
#define BLOCKING_MAIL_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <list>
#include <memory>
#include <atomic>

#include "actor-zeta/messaging/mail_box.hpp"

namespace actor_zeta {
    namespace messaging {
///
/// @brief
/// @tparam T
///
        class blocking_mail_queue final : public mail_box {
        public:
            using cache_type = std::list<message>;

            using queue_base_type = std::list<message>;

            using unique_lock = std::unique_lock<std::mutex>;
            using lock_guard = std::lock_guard<std::mutex>;

            blocking_mail_queue(const blocking_mail_queue &) = delete;

            blocking_mail_queue &operator=(const blocking_mail_queue &)= delete;

            blocking_mail_queue(blocking_mail_queue &&) = delete;

            blocking_mail_queue &operator=(blocking_mail_queue &&)= delete;

            blocking_mail_queue() = default;

            ~blocking_mail_queue() = default;

            enqueue_result put(message&& m) {
                enqueue_result status;
                {
                    lock_guard lock(mutex);
                    mail_queue.push_back(std::move(m));
                    status = enqueue_result::success;
                }
                cv.notify_one();
                return status;
            }

            message get() {
                if (local_queue.empty()) {
                    sync();
                }

                message tmp;

                if (!local_queue.empty()) {
                    tmp = std::move(local_queue.front());
                    local_queue.pop_front();
                }

                return tmp;
            }

            bool push_to_cache(messaging::message &&msg_ptr) {
                if (msg_ptr) {
                    switch (msg_ptr.priority()) {

                        case messaging::message_priority::low: {
                            low_priority_cache().push_back(std::move(msg_ptr));
                            return true;
                        }

                        case messaging::message_priority::normal: {
                            normal_priority_cache().push_back(std::move(msg_ptr));
                            return true;
                        }

                        case messaging::message_priority::high: {
                            high_priority_cache().push_back(std::move(msg_ptr));
                            return true;
                        }
                    }
                } else {
                    return false;
                }
            }

            messaging::message pop_to_cache() {
                messaging::message msg_ptr;
                if (!high_priority_cache().empty()) {
                    msg_ptr = std::move(high_priority_cache().front());
                    high_priority_cache().pop_front();
                    return msg_ptr;
                }

                if (!normal_priority_cache().empty()) {
                    msg_ptr =std::move( normal_priority_cache().front());
                    normal_priority_cache().pop_front();
                    return msg_ptr;
                }

                if (!low_priority_cache().empty()) {
                    msg_ptr = std::move(low_priority_cache().front());
                    low_priority_cache().pop_front();
                    return msg_ptr;
                }
                return msg_ptr;
            }

        private:

            cache_type &low_priority_cache() {
                return low_priority_cache_;
            }

            cache_type &normal_priority_cache() {
                return normal_priority_cache_;
            }

            cache_type &high_priority_cache() {
                return high_priority_cache_;
            }

            void sync() {
                lock_guard lock(mutex);
                local_queue.splice(local_queue.begin(), mail_queue);
            }

            mutable std::mutex mutex;
            std::condition_variable cv;
            
            queue_base_type mail_queue;
            queue_base_type local_queue;
            cache_type low_priority_cache_;
            cache_type normal_priority_cache_;
            cache_type high_priority_cache_;
        };
    }
}
#endif
