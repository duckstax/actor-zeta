#pragma once

#include "actor-zeta/base/address.hpp"
#include "actor-zeta/base/forwards.hpp"
#include "actor-zeta/detail/memory.hpp"

namespace actor_zeta {

    template<
        class ParentSupervisor,
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<base::supervisor_abstract, ChildrenSupervisor>::value>>
    auto spawn_supervisor(ParentSupervisor* ptr, Args&&... args) -> std::unique_ptr<ChildrenSupervisor, actor_zeta::pmr::deleter_t> {
        auto allocate_byte = sizeof(ChildrenSupervisor);
        auto allocate_byte_alignof = alignof(ChildrenSupervisor);
        void* buffer = ptr()->allocate(allocate_byte, allocate_byte_alignof);
        auto* supervisor = new (buffer) ChildrenSupervisor(ptr, std::forward<Args>(args)...);

        return {supervisor, actor_zeta::pmr::deleter_t(ptr())};
    }

    template<
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<base::supervisor_abstract, ChildrenSupervisor>::value>>
    auto spawn_supervisor(actor_zeta::pmr::memory_resource* ptr, Args&&... args) -> std::unique_ptr<ChildrenSupervisor, actor_zeta::pmr::deleter_t> {
        auto allocate_byte = sizeof(ChildrenSupervisor);
        auto allocate_byte_alignof = alignof(ChildrenSupervisor);
        void* buffer = ptr->allocate(allocate_byte, allocate_byte_alignof);
        auto* supervisor = new (buffer) ChildrenSupervisor(ptr, std::forward<Args>(args)...);

        return {supervisor, actor_zeta::pmr::deleter_t(ptr)};
    }

} // namespace actor_zeta
