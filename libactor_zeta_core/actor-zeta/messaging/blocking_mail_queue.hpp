#ifndef BLOCKING_MAIL_QUEUE_HPP
#define BLOCKING_MAIL_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <list>
#include <memory>
#include <atomic>

namespace actor_zeta {
    namespace messaging {
///
/// @enum enqueue_result
/// @brief
///
        enum class enqueue_result {
                    success,
                    unblocked_reader,
                    queue_closed
        };
///
/// @brief
/// @tparam T
///
        template<typename T>
        class blocking_mail_queue final {
        public:
            using pointer = T *;
            using const_pointer = const T *;
            using reference = T &;
            using const_reference = const T &;

            using cache_type = std::list<pointer>;

            using queue_base_type = std::list<pointer>;

            using unique_lock = std::unique_lock<std::mutex>;
            using lock_guard = std::lock_guard<std::mutex>;

            blocking_mail_queue(const blocking_mail_queue &) = delete;

            blocking_mail_queue &operator=(const blocking_mail_queue &)= delete;

            blocking_mail_queue(blocking_mail_queue &&) = default;

            blocking_mail_queue &operator=(blocking_mail_queue &&)= default;

            blocking_mail_queue() = default;

            ~blocking_mail_queue() = default;

            enqueue_result put(pointer m) {
                enqueue_result status;
                {
                    lock_guard lock(mutex);
                        mail_queue.push_back(m);
                        status = enqueue_result::success;
                }
                cv.notify_one();
                return status;
            }


            void sync() {
                lock_guard lock(mutex);
                local_queue.splice(local_queue.begin(), mail_queue);
            }

            pointer get() {
                if (local_queue.empty()) {
                    sync();
                }

                pointer tmp = nullptr;

                if (!local_queue.empty()) {
                    tmp = local_queue.front();
                    local_queue.pop_front();
                }

                return tmp;
            }

            cache_type &low_priority_cache() {
                return low_priority_cache_;
            }

            cache_type &normal_priority_cache() {
                return normal_priority_cache_;
            }

            cache_type &high_priority_cache() {
                return high_priority_cache_;
            }

        private:
            mutable std::mutex mutex;
            std::condition_variable cv;

            bool close;
            queue_base_type mail_queue;
            queue_base_type local_queue;
            cache_type low_priority_cache_;
            cache_type normal_priority_cache_;
            cache_type high_priority_cache_;
        };
    }
}
#endif