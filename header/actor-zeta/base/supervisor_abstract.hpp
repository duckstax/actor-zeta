#pragma once

#include <actor-zeta/base/behavior.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>

namespace actor_zeta { namespace base {

    /**
     * @class supervisor_abstract
     * @brief
     *
     * @tparam actor_traits
     */
    template<typename actor_traits>
    class supervisor_abstract
        : public actor_abstract
        , public intrusive_behavior_t<actor_traits> {
        using string_type = typename actor_traits::string_type;
        using memory_resource_ptr = typename actor_traits::memory_resource_ptr;

        using self_t = supervisor_abstract<actor_traits>;
        using self_ptr = self_t*;

    public:
        supervisor_abstract(memory_resource_ptr, string_type);

        template<class Supervisor>
        supervisor_abstract(Supervisor* supervisor, string_type type)
            : supervisor_abstract(static_cast<self_ptr>(supervisor), std::move(type)) {}

        ~supervisor_abstract() override {}

        inline auto scheduler() noexcept -> scheduler::scheduler_abstract_t* { return scheduler_impl(); }
        inline auto resource() const -> memory_resource_ptr { return intrusive_behavior_t<actor_traits>::resource(); }
        inline auto address() noexcept -> address_t { return address_t(this); }

    protected:
        virtual auto scheduler_impl() noexcept -> scheduler::scheduler_abstract_t* = 0;

        inline auto set_current_message(mailbox::message_ptr msg) -> void {
            current_message_ = msg.release();
        }
        inline auto current_message() -> mailbox::message* {
            return current_message_;
        }

    private:
        supervisor_abstract(self_ptr, string_type);

        mailbox::message* current_message_;
    };

    /**
     * @brief
     *
     * @tparam actor_traits
     * @tparam Supervisor
     */
    template<typename actor_traits, class Supervisor>
    class cooperative_supervisor : public supervisor_abstract<actor_traits> {
        using parent_t = supervisor_abstract<actor_traits>;

    public:
        using parent_t::address;
        using parent_t::resource;
        using parent_t::scheduler;
        using parent_t::supervisor_abstract;

    protected:
         template<
            class Inserter,
            class... Args>
        auto spawn_actor(const Inserter& inserter, actor_zeta::detail::pmr::memory_resource* ptr, Args&&... args) -> address_t {
            using Inserter_remove_reference =  type_traits::remove_reference_t<Inserter>;
            using call_trait =  type_traits::get_callable_trait_t<Inserter_remove_reference>;
            using Actor = type_traits::type_list_at_t<typename call_trait::args_types, 0>;
            //static_assert(std::is_pointer<Actor>::value,"not a pointer"); // @TODO static_assert !!!
            using Actor_clear_type = type_traits::decay_t<Actor>;
            using Actor_remove_pointer_type = typename std::remove_pointer<Actor_clear_type>::type;
            //static_assert(std::is_base_of<actor_abstract, Actor_remove_pointer_type>::value,"not heir"); // @TODO static_assert !!!

            auto* actor = actor_zeta::detail::pmr::allocate_ptr<Actor_remove_pointer_type, actor_zeta::detail::pmr::memory_resource*&, Args...>(
                //static_cast<Supervisor*>(this),
                ptr, ptr, std::forward<Args&&>(args)...);
            assert(actor);

            auto address = actor->address();
            inserter(actor);
            return address;
        }

        template<
            class Inserter,
            class... Args>
        auto spawn_supervisor(const Inserter& inserter, actor_zeta::detail::pmr::memory_resource* ptr, Args&&... args) -> address_t {
            using Inserter_remove_reference =  type_traits::remove_reference_t<Inserter>;
            using call_trait =  type_traits::get_callable_trait_t<Inserter_remove_reference>;
            using SupervisorChildren = type_traits::type_list_at_t<typename call_trait::args_types, 0>;
            //static_assert(std::is_pointer<SupervisorChildren>::value,"not a pointer"); // @TODO static_assert !!!
            using SupervisorChildren_clear_type = type_traits::decay_t<SupervisorChildren>;
            using SupervisorChildren_remove_pointer_type = typename std::remove_pointer<SupervisorChildren_clear_type>::type;
            //static_assert(std::is_base_of<supervisor_abstract, SupervisorChildren_remove_pointer_type>::value,"not heir"); // @TODO static_assert !!!

            auto* supervisor = actor_zeta::detail::pmr::allocate_ptr<SupervisorChildren_remove_pointer_type, actor_zeta::detail::pmr::memory_resource*&, Args...>(
                ptr, ptr, std::forward<Args&&>(args)...);
            assert(supervisor);

            auto address = supervisor->address();
            inserter(supervisor);
            return address;
        }
    };

    template<typename actor_traits>
    supervisor_abstract<actor_traits>::supervisor_abstract(memory_resource_ptr mr, string_type type)
        : actor_abstract(/*std::move(type)*/)
        , intrusive_behavior_t<actor_traits>(mr) {
    }

    template<typename actor_traits>
    supervisor_abstract<actor_traits>::supervisor_abstract(self_ptr ptr, string_type type)
        : actor_abstract(/*std::move(type)*/)
        , intrusive_behavior_t<actor_traits>(ptr->resource()) {
    }

}} // namespace actor_zeta::base
