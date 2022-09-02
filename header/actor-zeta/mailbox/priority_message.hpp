#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/mailbox/normal_priority_message.hpp>
#include <actor-zeta/mailbox/high_priority_message.hpp>

namespace actor_zeta { namespace mailbox {

    class priority_message {
    public:
        using mapped_type = mailbox::message;
        using task_size_type = size_t;
        using deficit_type = size_t;
        using unique_pointer = mailbox::message_ptr;

        priority_message() = default;
        priority_message(const priority_message&) = default;
        priority_message(priority_message&) = default;
        priority_message(priority_message&&) = default;
        auto operator=(const priority_message&) -> priority_message& = default;
        auto operator=(priority_message&) -> priority_message& = default;
        constexpr explicit priority_message(const type_traits::unit_t&) {}

        template<template<class> class Queue>
        static auto quantum(const Queue<high_priority_message>&, deficit_type x) noexcept -> deficit_type {
            return x + x;
        }

        template<class Queue>
        static auto quantum(const Queue&, deficit_type x) noexcept -> deficit_type {
            return x;
        }

        static auto id_of(const mailbox::message &msg) noexcept -> size_t {
            return msg.is_high_priority() ? 0 : 1;
        }
    };

}} // namespace actor_zeta::mailbox
