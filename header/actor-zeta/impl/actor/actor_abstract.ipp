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

    static void error_sync_contacts(detail::string_view name, detail::string_view error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    actor_abstract::~actor_abstract() {
    }

    actor_abstract::actor_abstract(std::string type)
        : communication_module(std::move(type)) {
    }

    auto actor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

}} // namespace actor_zeta::base
