#pragma once
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/detail/queue/cached_queue.hpp>
#include <actor-zeta/detail/queue/fixed_queue.hpp>
#include <actor-zeta/mail_box/priority_message.hpp>

namespace actor_zeta {

    using normal_priority_queue = detail::cached_queue<mail_box::normal_priority_message>;
    using high_priority_queue   = detail::cached_queue<mail_box::high_priority_message>;

    struct mailbox_policy {
        using deficit_type = size_t;
        using mapped_type = base::message;
        using unique_pointer = base::message_ptr;
        using queue_type = detail::fixed_queue<mail_box::priority_message, high_priority_queue, normal_priority_queue>;
    };

    static constexpr size_t high_priority_queue_index   = 0;
    static constexpr size_t normal_priority_queue_index = 1;

}