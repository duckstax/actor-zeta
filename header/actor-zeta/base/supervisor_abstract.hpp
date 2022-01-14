#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>

namespace actor_zeta { namespace base {

    class supervisor_abstract
        : public communication_module
        , public ref_counted {
    public:
#ifdef DEBUG
        supervisor_abstract(detail::pmr::memory_resource*, int64_t,std::string);

        template<class Supervisor>
        supervisor_abstract(Supervisor* supervisor, int64_t actor_id,std::string type)
            : supervisor_abstract(static_cast<supervisor_abstract*>(supervisor), actor_id,std::move(type)) {}
#elif
        supervisor_abstract(detail::pmr::memory_resource*, int64_t);

        template<class Supervisor>
        supervisor_abstract(Supervisor* supervisor, int64_t actor_id)
            : supervisor_abstract(static_cast<supervisor_abstract*>(supervisor), actor_id) {}
#endif
        ~supervisor_abstract() override;
        auto scheduler() noexcept -> scheduler::scheduler_abstract_t*;
        auto resource() const -> detail::pmr::memory_resource*;
        auto address() noexcept -> address_t;

    protected:
        using communication_module::add_handler;
        virtual auto scheduler_impl() noexcept -> scheduler::scheduler_abstract_t* = 0;
        auto set_current_message(message_ptr) -> void;
        auto current_message_impl() -> message* final;

    private:
#ifdef DEBUG
        supervisor_abstract(supervisor_abstract*,int64_t,std::string);
#elif
        supervisor_abstract(supervisor_abstract*, int64_t);
#endif
        message* current_message_;
        detail::pmr::memory_resource* memory_resource_;
    };

    template<class Supervisor>
    class cooperative_supervisor : public supervisor_abstract {
    public:
        using supervisor_abstract::address;
        using supervisor_abstract::resource;
        using supervisor_abstract::scheduler;
        using supervisor_abstract::supervisor_abstract;

    protected:
        using communication_module::add_handler;

        template<
            class Actor,
            class Inserter,
            class... Args,
            class = type_traits::enable_if_t<std::is_base_of<actor_abstract, Actor>::value>>
        auto spawn_actor(const Inserter& inserter, Args&&... args) -> address_t {
            auto allocate_byte = sizeof(Actor);
            auto allocate_byte_alignof = alignof(Actor);
            void* buffer = resource()->allocate(allocate_byte, allocate_byte_alignof);
            auto* actor = new (buffer) Actor(static_cast<Supervisor*>(this), std::forward<Args>(args)...);
            auto address = actor->address();
            inserter(actor);
            return address;
        }

        template<
            class SupervisorChildren,
            class Inserter,
            class... Args,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, SupervisorChildren>::value>>
        auto spawn_supervisor(const Inserter& inserter, Args&&... args) -> address_t {
            auto allocate_byte = sizeof(SupervisorChildren);
            auto allocate_byte_alignof = alignof(SupervisorChildren);
            void* buffer = resource()->allocate(allocate_byte, allocate_byte_alignof);
            auto* supervisor = new (buffer) SupervisorChildren(static_cast<Supervisor*>(this), std::forward<Args>(args)...);
            auto address = supervisor->address();
            inserter(supervisor);
            return address;
        }
    };

}} // namespace actor_zeta::base
