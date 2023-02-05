#pragma once

// clang-format off
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/detail/type_traits.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
// clang-format on

namespace actor_zeta {

    template<class T>
    auto make_message_ptr(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            T name) -> mailbox::message* {
        return detail::pmr::allocate_ptr<mailbox::message>(
            memory_resource,
            std::move(sender_),
            mailbox::make_message_id(static_cast<uint64_t>(name)));
    }

    template<class T, typename Arg>
    auto make_message_ptr(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            T name,
            Arg&& arg) -> mailbox::message* {
        return detail::pmr::allocate_ptr<mailbox::message>(
            memory_resource,
            std::move(sender_),
            mailbox::make_message_id(static_cast<uint64_t>(name)),
            std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<class T, typename... Args>
    auto make_message_ptr(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            T name,
            Args&&... args) -> mailbox::message* {
        return detail::pmr::allocate_ptr<mailbox::message>(
            memory_resource,
            std::move(sender_),
            mailbox::make_message_id(static_cast<uint64_t>(name)),
            std::move(detail::rtt(nullptr, std::forward<Args&&>(args)...)));
    }

    template<class T>
    auto make_message(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            T name) -> mailbox::message_ptr {
        using msgtype_t = mailbox::message;
        auto* message = detail::pmr::allocate_ptr<msgtype_t>(
            memory_resource,
            std::move(sender_), mailbox::make_message_id(static_cast<uint64_t>(name)));
        assert(message);
        return {message, detail::deleter_t<msgtype_t>(memory_resource)};
    }

    template<class T, typename Arg>
    auto make_message(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_, 
            T name,
            Arg&& arg) -> mailbox::message_ptr {
        using msgtype_t = mailbox::message;
        auto* message = detail::pmr::allocate_ptr<msgtype_t>(
            memory_resource,
            std::move(sender_),
            mailbox::make_message_id(static_cast<uint64_t>(name)),
            std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg))));
        assert(message);
        return {message, detail::deleter_t<msgtype_t>(memory_resource)};
    }

    template<class T, typename... Args>
    auto make_message(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            T name,
            Args&&... args) -> mailbox::message_ptr {
        using msgtype_t = mailbox::message;
        auto* message = detail::pmr::allocate_ptr<msgtype_t>(
            memory_resource,
            std::move(sender_),
            mailbox::make_message_id(static_cast<uint64_t>(name)),
            std::move(detail::rtt(nullptr, std::forward<Args&&>(args)...)));
        assert(message);
        return {message, detail::deleter_t<msgtype_t>(memory_resource)};
    }

    auto make_message(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            mailbox::message_id id) -> mailbox::message_ptr;

    template<typename Arg>
    auto make_message(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            mailbox::message_id id, Arg&& arg) -> mailbox::message_ptr {
        using msgtype_t = mailbox::message;
        auto* message = detail::pmr::allocate_ptr<msgtype_t>(
            memory_resource,
            std::move(sender_),
            id,
            std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg))));
        assert(message);
        return {message, detail::deleter_t<msgtype_t>(memory_resource)};
    }

    template<typename... Args>
    auto make_message(
            detail::pmr::memory_resource* memory_resource,
            base::address_t sender_,
            mailbox::message_id id, Args&&... args) -> mailbox::message_ptr {
        using msgtype_t = mailbox::message;
        auto* message = detail::pmr::allocate_ptr<msgtype_t>(
            memory_resource,
            std::move(sender_),
            id,
            std::move(detail::rtt(nullptr, std::forward<Args>(args)...)));
        assert(message);
        return {message, detail::deleter_t<msgtype_t>(memory_resource)};
    }

} // namespace actor_zeta