#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/detail/type_list.hpp>

namespace actor_zeta { namespace mail_box {

    class urgent_messages {
    public:
        using mapped_type = base::message;
        using task_size_type = size_t;
        using deficit_type = size_t;
        using unique_pointer = base::message_ptr;

        urgent_messages() = default;
        urgent_messages(const urgent_messages&) = default;
        auto operator=(const urgent_messages&) -> urgent_messages& = default;
        constexpr explicit urgent_messages(const type_traits::unit_t&) {}

        static auto task_size(const base::message&) noexcept -> task_size_type {
            return 1;
        }
    };

}} // namespace actor_zeta::mail_box
