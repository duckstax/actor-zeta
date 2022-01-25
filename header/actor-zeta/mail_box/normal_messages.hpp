#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/detail/type_list.hpp>

namespace actor_zeta { namespace mail_box {

    class normal_messages {
    public:
        using mapped_type = base::message;
        using task_size_type = size_t;
        using deficit_type = size_t;
        using unique_pointer = base::message_ptr;

        normal_messages() = default;
        normal_messages(const normal_messages&) = default;
        auto operator=(const normal_messages&) -> normal_messages& = default;
        constexpr explicit normal_messages(const type_traits::unit_t&) {}

        static auto task_size(const base::message&) noexcept -> task_size_type {
            return 1;
        }
    };

}} // namespace actor_zeta::mail_box
