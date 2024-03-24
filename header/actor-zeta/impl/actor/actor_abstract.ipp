#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <iostream>

namespace actor_zeta { namespace base {

    actor_abstract::~actor_abstract() {}

    auto actor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

    bool actor_abstract::enqueue(mailbox::message_ptr msg) {
        return enqueue(std::move(msg), nullptr);
    }

    auto actor_abstract::type() const noexcept -> const char* const {
        return type_impl();
    }


    bool actor_abstract::enqueue(mailbox::message_ptr msg, scheduler::execution_unit* e) {
        return enqueue_impl(std::move(msg), e);
    }

    auto actor_abstract::id() const -> id_t {
        return id_t{const_cast<actor_abstract*>(this)};
    }

}} // namespace actor_zeta::base
