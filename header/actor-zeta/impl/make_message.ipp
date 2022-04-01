#pragma once

// clang-format off
#include <actor-zeta/detail/type_traits.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
// clang-format on

namespace actor_zeta {

    auto make_message_ptr(base::address_t sender_, mailbox::message_id id) -> mailbox::message* {
        return new mailbox::message(std::move(sender_), id);
    }

    auto make_message(base::address_t sender_, mailbox::message_id id) -> mailbox::message_ptr {
        return mailbox::message_ptr(new mailbox::message(std::move(sender_), id));
    }

} // namespace actor_zeta