#pragma once
#include "detail/string_view.hpp"

// clang-format off
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
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

    communication_module::communication_module(std::string type, int64_t id)
        : type_(std::move(type))
        , id_(id) {}

    void communication_module::enqueue(message_ptr msg, scheduler::execution_unit* e) {
        enqueue_impl(std::move(msg), e);
    }

    auto communication_module::id() const -> int64_t {
        return id_;
    }

}} // namespace actor_zeta::base
