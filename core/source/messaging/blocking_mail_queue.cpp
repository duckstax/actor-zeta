#include <actor-zeta/messaging/blocking_mail_queue.hpp>
#include <actor-zeta/messaging/message.hpp>


namespace actor_zeta { namespace messaging {


        enqueue_result blocking_mail_queue::put(message &&m) {
            enqueue_result status;
            {
                lock_guard lock(mutex);
                mail_queue.push_back(std::move(m));
                status = enqueue_result::success;
            }
            cv.notify_one();
            return status;
        }

        message blocking_mail_queue::get() {
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

        bool blocking_mail_queue::push_to_cache(messaging::message &&msg_ptr) {
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

        messaging::message blocking_mail_queue::pop_to_cache() {
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

        blocking_mail_queue::cache_type &blocking_mail_queue::low_priority_cache() {
            return low_priority_cache_;
        }

        blocking_mail_queue::cache_type &blocking_mail_queue::normal_priority_cache() {
            return normal_priority_cache_;
        }

        blocking_mail_queue::cache_type &blocking_mail_queue::high_priority_cache() {
            return high_priority_cache_;
        }

        void blocking_mail_queue::sync() {
            lock_guard lock(mutex);
            local_queue.splice(local_queue.begin(), mail_queue);
        }

        blocking_mail_queue::~blocking_mail_queue() = default;

        blocking_mail_queue::blocking_mail_queue() = default;


    }
}