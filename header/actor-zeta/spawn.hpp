#pragma once

#include "send.hpp"

namespace actor_zeta {
    namespace detail {

        template<class Actor, class Supervisor, class Tuple, std::size_t... I>
        Actor* created_actor(Supervisor&& supervisor, Tuple&& args, type_traits::index_sequence<I...>) {
            return new Actor(supervisor, std::get<I>(args)...);
        }

    } // namespace detail

    template<
        class Actor,
        class Supervisor,
        class... Args>
    auto spawn_actor(Supervisor& supervisor, Args&&... args) -> void {
        using args_types = type_traits::type_list<Args...>;
        static constexpr size_t number_of_arguments = type_traits::type_list_size<args_types>::value;
        send(
            supervisor->address(),
            supervisor->address(),
            "spawn_actor",
            std::move(
                base::default_spawn_actor(
                    [&, args_ = std::move(std::tuple<Args&&...>(std::forward<Args&&>(args)...))](detail::pmr::memory_resource* resource) {
                        return detail::created_actor<Actor>(supervisor, args_, type_traits::make_index_sequence<number_of_arguments>{});
                    })));
    }

    template<
        class Supervisor,
        class... Args>
    auto spawn_supervisor(Args&&... args) -> std::unique_ptr<Supervisor> {
    }

} // namespace actor_zeta