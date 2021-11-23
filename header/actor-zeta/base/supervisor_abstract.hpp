#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>

namespace actor_zeta { namespace base {
    class supervisor_abstract : public communication_module {
    public:
        supervisor_abstract(detail::pmr::memory_resource*, std::string,int64_t id);
        supervisor_abstract(std::string,int64_t id);
        supervisor_abstract(supervisor_abstract*, std::string,int64_t id);
        ~supervisor_abstract() override;
        auto executor() noexcept -> executor::abstract_executor*;
        auto resource() const -> detail::pmr::memory_resource*;
        auto address() noexcept -> address_t;

    protected:
        template<
            class Actor,
            class Predicate,
            class... Args,
            class = type_traits::enable_if_t<std::is_base_of<actor_abstract, Actor>::value>>
        auto spawn_actor(Predicate predicate,Args&&... args) -> address_t {
            auto allocate_byte = sizeof(Actor);
            auto allocate_byte_alignof = alignof(Actor);
            void* buffer = resource()->allocate(allocate_byte, allocate_byte_alignof);
            auto* actor = new (buffer) Actor(this, std::forward<Args>(args)...);
            auto address = actor->address();
            predicate(actor);
            return address;
        }

        template<
            class Supervisor,
            class Predicate,
            class... Args,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, Supervisor>::value>>
        auto spawn_supervisor(Predicate predicate,Args&&... args) -> address_t {
            auto allocate_byte = sizeof(Supervisor);
            auto allocate_byte_alignof = alignof(Supervisor);
            void* buffer = resource()->allocate(allocate_byte, allocate_byte_alignof);
            auto* supervisor = new (buffer) Supervisor(this, std::forward<Args>(args)...);
            auto address = supervisor->address();
            predicate(supervisor);
            return address;
        }

        using communication_module::add_handler;
        virtual auto executor_impl() noexcept -> executor::abstract_executor* = 0;
        auto set_current_message(message_ptr) -> void;
        auto current_message_impl() -> message* final;

    private:
        message* current_message_;
        detail::pmr::memory_resource* memory_resource_;
    };

}} // namespace actor_zeta::base
