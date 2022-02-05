#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/detail/type_list.hpp>

namespace actor_zeta { namespace mail_box {

    class high_priority_message {
    public:
        using mapped_type = base::message;
        using task_size_type = size_t;
        using deficit_type = size_t;
        using unique_pointer = base::message_ptr;

        high_priority_message() = default;
        high_priority_message(const high_priority_message&) = default;
        auto operator=(const high_priority_message&) -> high_priority_message& = default;
        constexpr explicit high_priority_message(const type_traits::unit_t&) {}

        static auto task_size(const base::message&) noexcept -> task_size_type {
            return 1;
        }
    };

}} // namespace actor_zeta::mail_box
