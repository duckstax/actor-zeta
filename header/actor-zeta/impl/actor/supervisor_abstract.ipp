#pragma once
// clang-format off
#include <actor-zeta/base/supervisor_abstract.hpp>
// clang-format on
/// ------------------------------------------------
#include <actor-zeta/base/actor.hpp>

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <iostream>

namespace actor_zeta { namespace base {

    static void error_sync_contacts_in_supervisor(const std::string& name, const std::string& error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    using detail::aligned_allocate;
    using detail::aligned_deallocate;
    using detail::DEFAULT_ALIGNMENT;
    using detail::is_supported_alignment;

    supervisor_abstract::supervisor_abstract(detail::pmr::memory_resource* mr)
        : actor_abstract()
        , memory_resource_(mr) {
    }

    supervisor_abstract::supervisor_abstract(supervisor_abstract* ptr)
        : actor_abstract()
        , memory_resource_(ptr->resource()) {
    }

    supervisor_abstract::~supervisor_abstract() {}

    auto supervisor_abstract::current_message() -> mailbox::message* {
        return current_message_;
    }

    auto supervisor_abstract::set_current_message(mailbox::message_ptr msg) -> void {
        current_message_ = msg.release();
    }

    auto supervisor_abstract::resource() const noexcept -> detail::pmr::memory_resource* {
        return memory_resource_;
    }

    auto supervisor_abstract::scheduler() noexcept -> scheduler::scheduler_abstract_t* {
        return scheduler_impl();
    }

    auto supervisor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

}} // namespace actor_zeta::base
