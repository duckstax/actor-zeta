#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta { namespace base {

    actor_abstract::~actor_abstract() {
    }

    auto actor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

    void actor_abstract::enqueue(message_ptr msg) {
        enqueue(std::move(msg), nullptr);
    }

    auto actor_abstract::type() const -> detail::string_view {
        return detail::string_view(type_.data(), type_.size());
    }

    actor_abstract::actor_abstract(std::string type, int64_t id)
        : type_(std::move(type))
        , id_(id) {
    }

    void actor_abstract::enqueue(message_ptr msg, scheduler::execution_unit* e) {
        enqueue_impl(std::move(msg), e);
    }

    auto actor_abstract::id() const -> int64_t {
        return id_;
    }

}} // namespace actor_zeta::base
