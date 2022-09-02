#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/detail/type_list.hpp>

namespace actor_zeta { namespace mailbox {

    class high_priority_message {
    public:
        using mapped_type = mailbox::message;
        using task_size_type = size_t;
        using deficit_type = size_t;
        using unique_pointer = mailbox::message_ptr;

        high_priority_message() = default;
        high_priority_message(const high_priority_message&) = default;
        auto operator=(const high_priority_message&) -> high_priority_message& = default;
        constexpr explicit high_priority_message(const type_traits::unit_t&) {}

        static auto task_size(const mailbox::message&) noexcept -> task_size_type {
            return 1;
        }
    };

}} // namespace actor_zeta::mailbox
