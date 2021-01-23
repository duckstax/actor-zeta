#pragma once

#include <atomic>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>

#include "message.hpp"

namespace actor_zeta {
///
/// @brief
/// @tparam T
///
        enum class enqueue_result {
            success = 0,
            unblocked_reader,
            queue_closed
        };

        class blocking_mail_queue final {
        public:
            using cache_type = std::list<message>;

            using queue_base_type = std::list<message>;

            using unique_lock = std::unique_lock<std::mutex>;
            using lock_guard = std::lock_guard<std::mutex>;
            blocking_mail_queue();
            ~blocking_mail_queue();

            enqueue_result put(message&& m);

            message get();

            bool push_to_cache(message &&msg_ptr);

            message pop_to_cache();

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
