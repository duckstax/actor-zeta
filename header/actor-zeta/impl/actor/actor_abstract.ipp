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

    actor_abstract::actor_abstract(pmr::memory_resource*resource)
            : resource_(resource){}

    actor_abstract::~actor_abstract() {}

    auto actor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

    void actor_abstract::enqueue(mailbox::message_ptr msg) {
        enqueue_impl(std::move(msg));
    }

    auto actor_abstract::type() const noexcept -> const char* {
        return type_impl();
    }


    auto actor_abstract::id() const -> id_t {
        return id_t{const_cast<actor_abstract*>(this)};
    }

    actor_zeta::pmr::memory_resource* actor_abstract::resource() const noexcept {
        return resource_;
    }

}} // namespace actor_zeta::base
