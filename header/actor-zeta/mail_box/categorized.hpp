#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/mail_box/normal_messages.hpp>
#include <actor-zeta/mail_box/urgent_messages.hpp>

namespace actor_zeta { namespace mail_box {

    class categorized {
    public:
        using mapped_type = base::message;
        using task_size_type = size_t;
        using deficit_type = size_t;
        using unique_pointer = base::message_ptr;

        categorized() = default;
        categorized(const categorized&) = default;
        auto operator=(const categorized&) -> categorized& = default;
        constexpr explicit categorized(const type_traits::unit_t&) {}

        template<template<class> class Queue>
        static auto quantum(const Queue<urgent_messages>&, deficit_type x) noexcept -> deficit_type {
            return x + x;
        }

//        template<template<class> class Queue>
//        static auto quantum(const Queue<upstream_messages>& q, deficit_type) noexcept -> deficit_type {
//            return q.total_task_size();
//        }

        template<class Queue>
        static auto quantum(const Queue&, deficit_type x) noexcept -> deficit_type {
            return x;
        }

//        static auto id_of(const base::message& x) noexcept -> size_t {
//            return static_cast<size_t>(x.mid.category());
//        }
    };

}} // namespace actor_zeta::mail_box
