#pragma once
// clang-format off
#include <actor-zeta/base/supervisor_abstract.hpp>
// clang-format on
/// ------------------------------------------------
#include <actor-zeta/base/actor.hpp>

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <iostream>

namespace actor_zeta { namespace base {

    supervisor_abstract::supervisor_abstract(detail::pmr::memory_resource* mr, std::string name, int64_t id)
        : communication_module(std::move(name), id)
        , memory_resource_(mr) {
    }

    supervisor_abstract::supervisor_abstract(supervisor_abstract* ptr, std::string name, int64_t id)
        : communication_module(std::move(name), id)
        , memory_resource_(ptr->resource()) {
    }

    supervisor_abstract::~supervisor_abstract() {}

    auto supervisor_abstract::current_message_impl() -> message* {
        return current_message_;
    }

    auto supervisor_abstract::set_current_message(message_ptr msg) -> void {
        current_message_ = msg.release();
    }

    auto supervisor_abstract::resource() const -> detail::pmr::memory_resource* {
        return memory_resource_;
    }

    auto supervisor_abstract::scheduler() noexcept -> scheduler::scheduler_abstract_t* {
        return scheduler_impl();
    }

    auto supervisor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

    auto supervisor_abstract::clock() noexcept -> clock::clock_t& {
        return scheduler_impl()->clock();
    }

}} // namespace actor_zeta::base
