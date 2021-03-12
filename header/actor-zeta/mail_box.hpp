#pragma once
#include "actor-zeta/detail/intrusive/"

/// Stores asynchronous messages with default priority.
using normal_queue = intrusive::drr_cached_queue<policy::normal_messages>;

/// Stores asynchronous messages with hifh priority.
using urgent_queue = intrusive::drr_cached_queue<policy::urgent_messages>;



/// Configures the FIFO inbox with four nested queues:
///
///   1. Default asynchronous messages
///   2. High-priority asynchronous messages

struct mailbox_policy {
    using deficit_type = size_t;

    using mapped_type = mailbox_element;

    using unique_pointer = mailbox_element_ptr;

    using queue_type = intrusive::wdrr_fixed_multiplexed_queue<policy::categorized, urgent_queue, normal_queue>;
};

static constexpr size_t urgent_queue_index = 0;

static constexpr size_t normal_queue_index = 1;