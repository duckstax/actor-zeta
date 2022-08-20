#pragma once
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/mailbox/priority_message.hpp>
#include <actor-zeta/detail/queue/cached_queue.hpp>
#include <actor-zeta/detail/queue/fixed_queue.hpp>

namespace actor_zeta {

    //// @INFO Commented unused code, only single queue is used for now. @TODO for improvements priority
    //using normal_priority_queue = detail::cached_queue<mailbox::normal_priority_message>;
    using high_priority_queue   = detail::cached_queue<mailbox::high_priority_message>;

    struct mailbox_policy {
        using deficit_type = size_t;
        using mapped_type = mailbox::message;
        using unique_pointer = mailbox::message_ptr;
        using queue_type = detail::fixed_queue<mailbox::priority_message, high_priority_queue/*, normal_priority_queue*/>;
    };

    static constexpr size_t high_priority_queue_index   = 0;
    //static constexpr size_t normal_priority_queue_index = 1;

}