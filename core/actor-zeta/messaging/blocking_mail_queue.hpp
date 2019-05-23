#pragma once

#include <list>
#include <memory>
#include <atomic>
#include <actor-zeta/messaging/mail_box.hpp>
#include <actor-zeta/detail/spinlock.hpp>

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
            using lock_guard = std::lock_guard<spinlock>;

            blocking_mail_queue():mutex(true){}
            ~blocking_mail_queue() override = default;

            enqueue_result put(message&& m) override;

            message get() override;

            bool push_to_cache(messaging::message &&msg_ptr) override;

            messaging::message pop_to_cache() override;

        private:

            cache_type &cache();

            void sync();

            spinlock mutex;

            
            queue_base_type mail_queue;
            queue_base_type local_queue;
            cache_type cache_;
        };
    }
}
