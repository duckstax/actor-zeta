#pragma once

#include "actor-zeta/forwards.hpp"
#include "actor-zeta/base/address.hpp"

namespace actor_zeta {

    template<
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<base::supervisor_abstract, ChildrenSupervisor>::value>>
    auto  spawn_supervisor(Args&&... args) -> std::unique_ptr<ChildrenSupervisor> {
        return std::unique_ptr<ChildrenSupervisor>(new ChildrenSupervisor(std::forward<Args>(args)...));
    }

} // namespace actor_zeta
