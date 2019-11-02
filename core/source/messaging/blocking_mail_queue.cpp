#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message_header.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/blocking_mail_queue.hpp>



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
                cache().push_back(std::move(msg_ptr));
                return true;
            } else {
                return false;
            }
        }

        messaging::message blocking_mail_queue::pop_to_cache() {
            messaging::message msg_ptr;
            if (!cache().empty()) {
                msg_ptr = std::move(cache().front());
                cache().pop_front();
                return msg_ptr;
            }
            return msg_ptr;
        }

        blocking_mail_queue::cache_type &blocking_mail_queue::cache() {
            return cache_;
        }


        void blocking_mail_queue::sync() {
            lock_guard lock(mutex);
            local_queue.splice(local_queue.begin(), mail_queue);
        }

        blocking_mail_queue::~blocking_mail_queue() = default;

        blocking_mail_queue::blocking_mail_queue() = default;


    }
}