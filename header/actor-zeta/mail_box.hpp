#pragma once
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/detail/queue/cached_queue.hpp>
#include <actor-zeta/detail/queue/fixed_queue.hpp>
#include <actor-zeta/mail_box/categorized.hpp>

namespace actor_zeta {

    using normal_queue = detail::cached_queue<mail_box::normal_messages>;
    using urgent_queue = detail::cached_queue<mail_box::urgent_messages>;

    struct mailbox_policy {
        using deficit_type = size_t;
        using mapped_type = base::message;
        using unique_pointer = base::message_ptr;
        using queue_type = detail::fixed_queue<mail_box::categorized, urgent_queue, normal_queue>;
    };

    static constexpr size_t urgent_queue_index = 0;
    static constexpr size_t normal_queue_index = 1;

}