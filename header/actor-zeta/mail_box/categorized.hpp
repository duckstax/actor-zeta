#pragma once

#include "actor-zeta/forwards.hpp"
#include "message_priority.hpp"
#include "normal_messages.hpp"
#include "urgent_messages.hpp"

namespace actor_zeta { namespace mail_box {

    class categorized {
    public:
        // -- member types -----------------------------------------------------------

        using mapped_type = message;

        using task_size_type = size_t;

        using deficit_type = size_t;

        using unique_pointer = message_ptr;

        // -- constructors, destructors, and assignment operators --------------------

        categorized() = default;

        categorized(const categorized&) = default;

        categorized& operator=(const categorized&) = default;

        constexpr categorized(unit_t) {}

        template<template<class> class Queue>
        static deficit_type
        quantum(const Queue<urgent_messages>&, deficit_type x) noexcept {
            // Allow actors to consume twice as many urgent as normal messages per
            // credit round.
            return x + x;
        }

        template<template<class> class Queue>
        static deficit_type
        quantum(const Queue<upstream_messages>& q, deficit_type) noexcept {
            // Allow actors to consume *all* upstream messages. They are lightweight by
            // design and require little processing.
            return q.total_task_size();
        }

        template<class Queue>
        static deficit_type quantum(const Queue&, deficit_type x) noexcept {
            return x;
        }

        static size_t id_of(const mailbox_element& x) noexcept {
            return static_cast<size_t>(x.mid.category());
        }
    };

}} // namespace actor_zeta::mail_box
