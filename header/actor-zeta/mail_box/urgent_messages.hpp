#pragma once

#include "actor-zeta/forwards.hpp"
#include "caf/unit.hpp"

namespace actor_zeta { namespace mail_box {

    /// Configures a cached DRR queue for holding asynchronous messages with
    /// default priority.
    class urgent_messages {
    public:
        // -- member types -----------------------------------------------------------

        using mapped_type = message;

        using task_size_type = size_t;

        using deficit_type = size_t;

        using unique_pointer = message_ptr;

        urgent_messages() = default;

        urgent_messages(const urgent_messages&) = default;

        urgent_messages& operator=(const urgent_messages&) = default;

        constexpr urgent_messages(unit_t) {
            // nop
        }

        static task_size_type task_size(const mailbox_element&) noexcept {
            return 1;
        }
    };

}} // namespace actor_zeta::mail_box
