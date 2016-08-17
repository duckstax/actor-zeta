#ifndef BLOCKING_MAIL_QUEUE_HPP
#define BLOCKING_MAIL_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <list>
#include <memory>
#include <atomic>

namespace actor_zeta {
    namespace messaging {
        template<typename T>
        class blocking_mail_queue {
        public:
            using pointer = T *;
            using const_pointer = const T *;
            using reference = T &;
            using const_reference = const T &;

            using unique_lock = std::unique_lock<std::mutex>;
            using lock_guard=std::lock_guard<std::mutex>;

            blocking_mail_queue() : size_(0) {};

            ~blocking_mail_queue() {}

            bool put(pointer m) {
                bool status;
                {
                    lock_guard lock(mutex);
                    //if (mail_queue.empty())
                    //    cv.notify_one();
                    mail_queue.push_back(m);
                    status = true;
                }
                ++size_;
                cv.notify_one();
                return status;
            }

            pointer get() {
                pointer tmp = nullptr;
                {
                    unique_lock lock(mutex);
                    if (!empty()) {
                        tmp = mail_queue.front();
                        mail_queue.pop_front();
                        --size_;
                    }
                }
                return tmp;
            }

            size_t size() {
                return size_;
            }

            bool empty() {
                return size_ == 0;
            }

        private:
            mutable std::mutex mutex;
            std::condition_variable cv;
            std::list<pointer> mail_queue;
            std::atomic<size_t> size_;
        };
    }
}
#endif