#pragma once

#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/base/address.hpp>

namespace actor_zeta {

    template<
        class actor_traits,
        class ParentSupervisor,
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<
            std::is_base_of<
                actor_zeta::base::supervisor_abstract<actor_traits>,
                ChildrenSupervisor>::value>>
    auto spawn_supervisor(
            ParentSupervisor* ptr,
            Args&&... args)
        -> typename actor_traits::template unique_ptr_type<ChildrenSupervisor> {

        auto* supervisor = actor_zeta::detail::pmr::allocate_ptr<ChildrenSupervisor, Args...>(
            ptr->resource(),
            ptr, std::forward<Args&&>(args)...);
        assert(supervisor);

        return {supervisor, typename actor_traits::template deleter_type<ChildrenSupervisor>(ptr->resource())};
    }

    template<
        class actor_traits,
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<
            std::is_base_of<
                actor_zeta::base::supervisor_abstract<actor_traits>,
                ChildrenSupervisor>::value>>
    auto spawn_supervisor(
            actor_zeta::detail::pmr::memory_resource* ptr,
            Args&&... args)
        -> typename actor_traits::template unique_ptr_type<ChildrenSupervisor> {

        auto* supervisor = actor_zeta::detail::pmr::allocate_ptr<ChildrenSupervisor, actor_zeta::detail::pmr::memory_resource*&, Args...>(
            ptr, ptr, std::forward<Args&&>(args)...);
        assert(supervisor);

        return {supervisor, typename actor_traits::template deleter_type<ChildrenSupervisor>(ptr)};
    }

} // namespace actor_zeta
