#ifndef MAIL_BOX_HPP
#define MAIL_BOX_HPP

#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace messaging {

///
/// @enum enqueue_result
/// @brief
///
        enum class enqueue_result {
            success = 0,
            unblocked_reader,
            queue_closed
        };

        struct mail_box {
            mail_box() = default;
            mail_box(const mail_box &) = delete;
            mail_box &operator=(const mail_box &)= delete;
            mail_box(mail_box &&) = delete;
            mail_box &operator=(mail_box &&)= delete;
            virtual ~ mail_box() = default;
            /// thread-safe
            virtual enqueue_result put(messaging::message&&)=0;
            virtual messaging::message get() = 0;
            ///non thread safe
            virtual bool push_to_cache(messaging::message &&msg_ptr) = 0;
            virtual messaging::message pop_to_cache() =0;
        };
    }
}
#endif //PROJECT_MAIL_BOX_HPP
