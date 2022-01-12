#pragma once

#include "caf/fwd.hpp"
#include "caf/mailbox_element.hpp"
#include "caf/unit.hpp"

namespace actor_zeta { namespace mail_box {

    /// Configures a cached DRR queue for holding asynchronous messages with
    /// default priority.
    class normal_messages {
    public:
        // -- member types -----------------------------------------------------------

        using mapped_type = mailbox_element;

        using task_size_type = size_t;

        using deficit_type = size_t;

        using unique_pointer = mailbox_element_ptr;

        // -- constructors, destructors, and assignment operators --------------------

        normal_messages() = default;

        normal_messages(const normal_messages&) = default;

        normal_messages& operator=(const normal_messages&) = default;

        constexpr normal_messages(unit_t) {}

        static task_size_type task_size(const mailbox_element&) noexcept {
            return 1;
        }
    };

}} // namespace actor_zeta::mail_box
