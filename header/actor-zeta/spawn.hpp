#pragma once

#include "send.hpp"

namespace actor_zeta {
    namespace detail {

        template<
            class Actor,
            class Tuple, std::size_t... I,
            class = type_traits::enable_if_t<std::is_base_of<actor_abstract, Actor>::value>>
        Actor* created_actor(actor_zeta::supervisor_abstract* supervisor, Tuple&& args, type_traits::index_sequence<I...>) {
            return new Actor(supervisor, std::get<I>(args)...);
        }

        template<
            class ChildrenSupervisor,
            class Tuple, std::size_t... I,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, ChildrenSupervisor>::value>>
        ChildrenSupervisor* created_supervisor(actor_zeta::supervisor_abstract*supervisor, Tuple&& args, type_traits::index_sequence<I...>) {
            return new ChildrenSupervisor(supervisor, std::get<I>(args)...);
        }

    } // namespace detail

    template<
        class Actor,
        class Supervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<actor_abstract, Actor>::value>>
    auto spawn_actor(Supervisor& supervisor, Args&&... args) -> void {
        using args_types = type_traits::type_list<Args...>;
        static constexpr size_t number_of_arguments = type_traits::type_list_size<args_types>::value;
        send(
            supervisor->address(),
            supervisor->address(),
            "spawn_actor",
            std::move(
                base::default_spawn_actor(
                    [&, args_ = std::move(std::tuple<Args&&...>(std::forward<Args&&>(args)...))](actor_zeta::supervisor_abstract* ptr) {
                        return detail::created_actor<Actor>(ptr, args_, type_traits::make_index_sequence<number_of_arguments>{});
                    })));
    }

    template<
        class ChildrenSupervisor,
        class ParentSupervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, ChildrenSupervisor>::value>>
    auto spawn_supervisor(ParentSupervisor& supervisor, Args&&... args) -> void {
        using args_types = type_traits::type_list<Args...>;
        static constexpr size_t number_of_arguments = type_traits::type_list_size<args_types>::value;
        send(
            supervisor->address(),
            supervisor->address(),
            "spawn_supervisor",
            std::move(
                base::default_spawn_actor(
                    [&, args_ = std::move(std::tuple<Args&&...>(std::forward<Args&&>(args)...))](actor_zeta::supervisor_abstract* ptr) {
                        return detail::created_supervisor<ChildrenSupervisor>(ptr, args_, type_traits::make_index_sequence<number_of_arguments>{});
                    })));
    }

} // namespace actor_zeta