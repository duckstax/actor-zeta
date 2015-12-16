#ifndef BLOCKING_MAIL_QUEUE_HPP
#define BLOCKING_MAIL_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <list>
#include <memory>

#include "mail_box.hpp"

namespace actor_model {
    namespace messaging {
        template<typename T>
        class blocking_mail_queue final : public mail_box<T> {
        public:
            using unique_lock = std::unique_lock<std::mutex>;
            using lock_guard=std::lock_guard<std::mutex>;

            blocking_mail_queue() : size_(0) { };

            ~blocking_mail_queue() { }

            bool put(T &&m) override {
                bool status;
                {
                    lock_guard lock(mutex);
                    mail_queue.emplace_back(std::forward<T>(m));
                    status = true;
                }
                cv.notify_one();
                ++size_;
                return status;
            }

            T get() override {
                unique_lock lock(mutex);
                T tmp = std::forward<T>(mail_queue.front());
                mail_queue.pop_front();
                --size_;
                return tmp;
            }

            std::vector<T> getAll() override {
                std::vector<T> tmp;
                {
                    unique_lock lock(mutex);
                    for (auto &&i:mail_queue) {
                        tmp.emplace_back(std::forward<T>(i));
                    }
                    mail_queue.clear();
                }
                cv.notify_one();
                size_ = 0;
                return tmp;
            }

            size_t size() override {
                return size_;
            }

            bool empty() override {
                return size_ != 0;
            }

        private:
            mutable std::mutex mutex;
            std::condition_variable cv;
            std::list<T> mail_queue;
            std::atomic<size_t> size_;
        };
    }
}
#endif