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

    static void error_sync_contacts(const std::string& name, const std::string& error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    auto actor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

    void actor_abstract::enqueue(mailbox::message_ptr msg) {
        enqueue(std::move(msg), nullptr);
    }

    void actor_abstract::enqueue(mailbox::message_ptr msg, scheduler::execution_unit* e) {
        enqueue_impl(std::move(msg), e);
    }

    auto actor_abstract::id() const -> id_t {
        return id_t{const_cast<actor_abstract*>(this)};
    }

    auto actor_abstract::type() const -> const char* const {
//#ifdef DEBUG
//        return type_.data();
//#else
        return nullptr;
//#endif
    }

    actor_abstract::actor_abstract(
//#ifdef DEBUG
//        std::string type
//#endif
    ) {
//#ifdef DEBUG
//        type_ = std::move(type);
//#else
//        std::move(type);
//#endif
    }

}} // namespace actor_zeta::base
