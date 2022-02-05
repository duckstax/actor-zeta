#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/mail_box/normal_priority_message.hpp>
#include <actor-zeta/mail_box/high_priority_message.hpp>

namespace actor_zeta { namespace mail_box {

    class priority_message {
    public:
        using mapped_type = base::message;
        using task_size_type = size_t;
        using deficit_type = size_t;
        using unique_pointer = base::message_ptr;

        priority_message() = default;
        priority_message(const priority_message&) = default;
        auto operator=(const priority_message&) -> priority_message& = default;
        constexpr explicit priority_message(const type_traits::unit_t&) {}

        template<template<class> class Queue>
        static auto quantum(const Queue<high_priority_message>&, deficit_type x) noexcept -> deficit_type {
            return x + x;
        }

        template<class Queue>
        static auto quantum(const Queue&, deficit_type x) noexcept -> deficit_type {
            return x;
        }

        static auto id_of(const base::message &msg) noexcept -> size_t {
            return msg.is_high_priority() ? 0 : 1;
        }
    };

}} // namespace actor_zeta::mail_box
