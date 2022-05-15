#pragma once

#include "actor-zeta/detail/callable_trait.hpp"
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>

namespace actor_zeta { namespace base {

    class supervisor_abstract
        : public communication_module
        , public ref_counted
        , public intrusive_behavior_t {
    public:
        supervisor_abstract(detail::pmr::memory_resource*, std::string);

        template<class Supervisor>
        supervisor_abstract(Supervisor* supervisor, std::string type)
            : supervisor_abstract(static_cast<supervisor_abstract*>(supervisor), std::move(type)) {}

        ~supervisor_abstract() override;
        auto scheduler() noexcept -> scheduler::scheduler_abstract_t*;
        auto resource() const -> detail::pmr::memory_resource*;
        auto address() noexcept -> address_t;

    protected:
        virtual auto scheduler_impl() noexcept -> scheduler::scheduler_abstract_t* = 0;
        auto set_current_message(mailbox::message_ptr) -> void;
        auto current_message() -> mailbox::message*;

    private:
        supervisor_abstract(supervisor_abstract*, std::string);
        mailbox::message* current_message_;
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
        template<
            class Inserter,
            class... Args>
        auto spawn_actor(const Inserter& inserter, Args&&... args) -> address_t {
            using Inserter_remove_reference_t =  type_traits::remove_reference_t<Inserter>;
            using call_trait =  type_traits::get_callable_trait_t<Inserter_remove_reference_t>;
            using Actor = type_traits::type_list_at_t<typename call_trait::args_types, 0>;
            static_assert(std::is_pointer<Actor>::value);
            using Actor_clear_type = type_traits::decay_t<Actor>;
            using Actor_not_pointer_type = typename std::remove_pointer<Actor_clear_type>::type;
            static_assert(std::is_base_of<actor_abstract, Actor_not_pointer_type>::value,"");

            auto allocate_byte = sizeof(Actor_not_pointer_type);
            auto allocate_byte_alignof = alignof(Actor_not_pointer_type);
            void* buffer = resource()->allocate(allocate_byte, allocate_byte_alignof);
            auto* actor = new (buffer) Actor_not_pointer_type(static_cast<Supervisor*>(this), std::forward<Args>(args)...);
            auto address = actor->address();
            inserter(actor);
            return address;
        }

        template<
            class Inserter,
            class... Args>
        auto spawn_supervisor(const Inserter& inserter, Args&&... args) -> address_t {
            using Inserter_remove_reference_t =  type_traits::remove_reference_t<Inserter>;
            using call_trait =  type_traits::get_callable_trait_t<Inserter_remove_reference_t>;
            using SupervisorChildren = type_traits::type_list_at_t<typename call_trait::args_types, 0>;
            static_assert(std::is_pointer<SupervisorChildren>::value);
            using SupervisorChildren_clear_type = type_traits::decay_t<SupervisorChildren>;
            using SupervisorChildren_not_pointer_type = typename std::remove_pointer<SupervisorChildren_clear_type>::type;
            static_assert(std::is_base_of<actor_abstract, SupervisorChildren_not_pointer_type>::value,"");


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
