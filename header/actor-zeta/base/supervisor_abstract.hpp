#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    using default_spawn_actor = std::function<actor(detail::pmr::memory_resource*)>;
    using default_spawn_supervisor = std::function<supervisor(detail::pmr::memory_resource*)>;

    class supervisor_t : public communication_module {
    public:
        supervisor_t(detail::pmr::memory_resource*,std::string);
        ~supervisor_t() override;
        auto executor() noexcept -> executor::abstract_executor*;
        using communication_module::broadcast;
        auto resource() const -> detail::pmr::memory_resource*;

    protected:
        using communication_module::add_handler;
        virtual auto executor_impl() noexcept -> executor::abstract_executor* = 0;
        virtual auto add_actor_impl(actor) -> void = 0;
        virtual auto add_supervisor_impl(supervisor) -> void = 0;

        auto set_current_message(message_ptr) -> void;
        auto current_message() -> message* final;

    private:
        auto spawn_actor(default_spawn_actor&) -> void;
        auto spawn_supervisor(default_spawn_supervisor&) -> void;
        message* current_message_;
        detail::pmr::memory_resource* memory_resource_;
    };

}} // namespace actor_zeta::base