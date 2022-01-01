#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on


#include <iostream>

namespace actor_zeta { namespace base {

    actor_abstract::~actor_abstract() {
    }

    actor_abstract::actor_abstract(std::string type,int64_t id)
        : communication_module(std::move(type),id) {
    }

    auto actor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

}} // namespace actor_zeta::base
