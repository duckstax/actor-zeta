#pragma once

// clang-format off
#include <actor-zeta/detail/type_traits.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
// clang-format on

namespace actor_zeta {

    auto make_message_ptr(base::address_t sender_, mailbox::message_id id) -> mailbox::message*;
    template<typename Arg>
    auto make_message_ptr(base::address_t sender_, mailbox::message_id id, Arg&& arg) -> mailbox::message* {
        return new mailbox::message(std::move(sender_), id, std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<typename... Args>
    auto make_message_ptr(base::address_t sender_, mailbox::message_id id, Args&&... args) -> mailbox::message* {
        return new mailbox::message(std::move(sender_), id, std::move(detail::rtt(nullptr, std::forward<Args>(args)...)));
    }

    auto make_message(base::address_t sender_, mailbox::message_id id) -> mailbox::message_ptr;

    template<typename Arg>
    auto make_message(base::address_t sender_, mailbox::message_id id, Arg&& arg) -> mailbox::message_ptr {
        return mailbox::message_ptr(new mailbox::message(std::move(sender_), id, std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg)))));
    }

    template<typename... Args>
    auto make_message(base::address_t sender_, mailbox::message_id id, Args&&... args) -> mailbox::message_ptr {
        return mailbox::message_ptr(new mailbox::message(std::move(sender_), id, std::move(detail::rtt(nullptr, std::forward<Args>(args)...))));
    }

} // namespace actor_zeta