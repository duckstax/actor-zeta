#pragma once

#include "actor-zeta/base/forwards.hpp"
#include "actor-zeta/detail/memory_resource.hpp"

namespace actor_zeta {

    template<
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<base::supervisor_abstract, ChildrenSupervisor>::value>>
    auto  spawn_supervisor(actor_zeta::detail::pmr::memory_resource*resource,Args&&... args) noexcept -> std::unique_ptr<ChildrenSupervisor> {
        auto allocate_byte = sizeof(ChildrenSupervisor);
        auto allocate_byte_alignof = alignof(ChildrenSupervisor);
        void* buffer = resource->allocate(allocate_byte, allocate_byte_alignof);
        auto* supervisor = new (buffer) ChildrenSupervisor(resource, std::forward<Args>(args)...);
        return std::unique_ptr<ChildrenSupervisor>(supervisor);
    }

} // namespace actor_zeta
