#pragma once

#include "actor-zeta/base/address.hpp"
#include "actor-zeta/base/forwards.hpp"

namespace actor_zeta {

    class deleter final {
    public:
        deleter(actor_zeta::pmr::memory_resource* ptr)
            : ptr_(ptr) {}

        template<class ChildrenSupervisor>
        void operator()(ChildrenSupervisor* cs_ptr) {
            ptr_->deallocate(cs_ptr, sizeof(ChildrenSupervisor));
        }

    private:
        actor_zeta::pmr::memory_resource* ptr_;
    };

    template<
        class ParentSupervisor,
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<base::supervisor_abstract, ChildrenSupervisor>::value>>
    auto spawn(ParentSupervisor* ptr, Args&&... args) -> std::unique_ptr<ChildrenSupervisor, deleter> {
        auto allocate_byte = sizeof(ChildrenSupervisor);
        auto allocate_byte_alignof = alignof(ChildrenSupervisor);
        void* buffer = ptr()->allocate(allocate_byte, allocate_byte_alignof);
        auto* supervisor = new (buffer) ChildrenSupervisor(ptr, std::forward<Args>(args)...);

        return {supervisor, deleter(ptr())};
    }

    template<
        class ChildrenSupervisor,
        class... Args,
        class = type_traits::enable_if_t<std::is_base_of<base::supervisor_abstract, ChildrenSupervisor>::value>>
    auto spawn(actor_zeta::pmr::memory_resource* ptr, Args&&... args) -> std::unique_ptr<ChildrenSupervisor, deleter> {
        auto allocate_byte = sizeof(ChildrenSupervisor);
        auto allocate_byte_alignof = alignof(ChildrenSupervisor);
        void* buffer = ptr->allocate(allocate_byte, allocate_byte_alignof);
        auto* supervisor = new (buffer) ChildrenSupervisor(ptr, std::forward<Args>(args)...);

        return {supervisor, deleter(ptr)};
    }

} // namespace actor_zeta
