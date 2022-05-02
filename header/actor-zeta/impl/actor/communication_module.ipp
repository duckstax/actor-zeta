#pragma once

// clang-format off
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta { namespace base {

    void communication_module::enqueue(mailbox::message_ptr msg) {
        enqueue(std::move(msg), nullptr);
    }

    auto communication_module::type() const -> const char* const {
#ifdef DEBUG
        return type_.data();
#else
        return nullptr;
#endif
    }

    communication_module::~communication_module() {}

    communication_module::communication_module(std::string type) {
#ifdef DEBUG
        type_ = std::move(type);
#else
        std::move(type);
#endif
    }


    void communication_module::enqueue(mailbox::message_ptr msg, scheduler::execution_unit* e) {
        enqueue_impl(std::move(msg), e);
    }

    auto communication_module::id() const -> id_t {
        return id_t{const_cast<communication_module*>(this)};
    }

}} // namespace actor_zeta::base
