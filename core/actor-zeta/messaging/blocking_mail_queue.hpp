#ifndef BLOCKING_MAIL_QUEUE_HPP
#define BLOCKING_MAIL_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <list>
#include <memory>
#include <atomic>
#include <actor-zeta/messaging/mail_box.hpp>

namespace actor_zeta { namespace messaging {
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
            blocking_mail_queue();
            ~blocking_mail_queue();

            enqueue_result put(message&& m);

            message get();

            bool push_to_cache(messaging::message &&msg_ptr);

            messaging::message pop_to_cache();

        private:

            cache_type &cache();

            void sync();

            mutable std::mutex mutex;
            std::condition_variable cv;
            
            queue_base_type mail_queue;
            queue_base_type local_queue;
            cache_type cache_;
        };
    }
}
#endif
