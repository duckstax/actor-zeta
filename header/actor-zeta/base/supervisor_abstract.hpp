#pragma once

#include <actor-zeta/clock/clock.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/base/behavior.hpp>

namespace actor_zeta { namespace base {

    class supervisor_abstract
        : public actor_abstract
        , public ref_counted {
    public:
        auto scheduler() noexcept -> scheduler::scheduler_abstract_t*;
        auto resource() const -> detail::pmr::memory_resource*;
        auto clock() noexcept -> clock::clock_t&;

    protected:
        supervisor_abstract(detail::pmr::memory_resource*, std::string, int64_t);
        supervisor_abstract(supervisor_abstract*, std::string, int64_t);
        ~supervisor_abstract() override;

        virtual auto scheduler_impl() noexcept -> scheduler::scheduler_abstract_t* = 0;
        auto set_current_message(message_ptr) -> void;
        auto current_message() -> message* ;

        behavior_container behavior_;

    private:
        detail::pmr::memory_resource* memory_resource_;
        message* current_message_;
    };

    template<class Supervisor>
    class cooperative_supervisor
        : public supervisor_abstract {
    public:
        using supervisor_abstract::address;
        using supervisor_abstract::resource;
        using supervisor_abstract::scheduler;
        using supervisor_abstract::supervisor_abstract;

    protected:

        cooperative_supervisor(Supervisor* supervisor, std::string type, int64_t actor_id)
            : supervisor_abstract(static_cast<supervisor_abstract*>(supervisor), std::move(type), actor_id) {}

        /// ----- deprecated

        template<class F>
        auto add_handler(behavior_t::key_type name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            behavior_.on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(behavior_t::key_type name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            behavior_.on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        template<class T,typename F>
        auto add_handler(behavior_t::key_type name,T*ptr, F&& f) -> void{
            behavior_.on(name, make_handler(std::forward<F>(f), ptr));
        }

        /// ----- deprecated

        template<class F>
        void behavior(const F&f){
            behavior_t tmp(this);
            f(tmp);
            behavior_.assign(tmp);
        }

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
