#pragma once
#include "detail/string_view.hpp"
#include <iostream>
#include <vector>

// clang-format off
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta { namespace base {

    void communication_module::enqueue(message_ptr msg) {
        enqueue(std::move(msg), nullptr);
    }

    auto communication_module::type() const -> detail::string_view {
        return detail::string_view(type_.data(), type_.size());
    }

    communication_module::~communication_module() {}

    communication_module::communication_module(std::string type)
        : type_(std::move(type)) {}

    void communication_module::enqueue(message_ptr msg, scheduler::execution_unit* e) {
        enqueue_base(std::move(msg), e);
    }
    auto communication_module::current_message() -> message* {
        return current_message_impl();
    }

}} // namespace actor_zeta::base
