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
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <iostream>

namespace actor_zeta { namespace base {

    static void error_sync_contacts_in_supervisor(detail::string_view name, detail::string_view error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    using detail::aligned_allocate;
    using detail::aligned_deallocate;
    using detail::DEFAULT_ALIGNMENT;
    using detail::is_supported_alignment;

    class new_delete_resource final : public detail::pmr::memory_resource {
    public:
    private:
        void* do_allocate(std::size_t bytes, std::size_t alignment = DEFAULT_ALIGNMENT) override {
            alignment = (is_supported_alignment(alignment)) ? alignment : DEFAULT_ALIGNMENT;
            return aligned_allocate(bytes, alignment, [](std::size_t size) { return ::operator new(size); });
        }

        void do_deallocate(void* p, std::size_t bytes, std::size_t alignment = DEFAULT_ALIGNMENT) override {
            aligned_deallocate(p, bytes, alignment, [](void* p) { ::operator delete(p); });
        }

        bool do_is_equal(const memory_resource& other) const noexcept override { return &other == this; }
    };

    supervisor_abstract::supervisor_abstract(detail::pmr::memory_resource* mr, std::string name,int64_t id)
        : communication_module(std::move(name),id)
        , memory_resource_(mr) {

    }

    supervisor_abstract::supervisor_abstract(std::string name,int64_t id)
        : communication_module(std::move(name),id)
        , memory_resource_(new new_delete_resource) {

    }

    supervisor_abstract::supervisor_abstract(supervisor_abstract* ptr, std::string name,int64_t id)
        : communication_module(std::move(name),id)
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

    auto supervisor_abstract::executor() noexcept -> executor::abstract_executor* {
        return executor_impl();
    }

    auto supervisor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

}} // namespace actor_zeta::base
