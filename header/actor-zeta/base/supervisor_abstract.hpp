#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    using default_spawn_actor = std::function<actor(detail::pmr::memory_resource*)>;
    using default_spawn_supervisor = std::function<supervisor(detail::pmr::memory_resource*)>;

    class supervisor_t : public communication_module {
    public:
        supervisor_t(std::string, detail::pmr::memory_resource*);
        ~supervisor_t() override;
        auto executor() noexcept -> executor::abstract_executor*;
        auto join_actor(default_spawn_actor&) -> actor_address;
        auto join_supervisor(default_spawn_supervisor&) -> actor_address;
        using communication_module::broadcast;
        auto resource() const -> detail::pmr::memory_resource*;

    protected:
        using communication_module::add_handler;
        virtual auto executor_imp() noexcept -> executor::abstract_executor* = 0;
        virtual auto join_imp(actor) -> actor_address = 0;
        virtual auto join_imp(supervisor) -> actor_address = 0;


        auto set_current_message(message_ptr) -> void;
        auto current_message() -> message* final;

    private:
        message* current_message_;
        detail::pmr::memory_resource* memory_resource_;
    };

}} // namespace actor_zeta::base