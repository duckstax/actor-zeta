#pragma once

// clang-format off
#include <actor-zeta/detail/type_traits.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
// clang-format on

namespace actor_zeta {

    auto make_message(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            mailbox::message_id id) -> mailbox::message_ptr {
        using msgtype_t = mailbox::message;
        auto* message = detail::pmr::allocate_ptr<msgtype_t>(
            memory_resource,
            std::move(sender_), id);
        assert(message);
        return {message, detail::deleter_t<msgtype_t>(memory_resource)};
    }

} // namespace actor_zeta