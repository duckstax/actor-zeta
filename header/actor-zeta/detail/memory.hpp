#pragma once

#include <cassert>

#include "actor-zeta/detail/pmr/aligned_allocate.hpp"
#include "memory_resource.hpp"

namespace actor_zeta { namespace pmr {

    template<class Target, class... Args>
    Target* allocate_ptr(actor_zeta::pmr::memory_resource* resource, Args&&... args) {
        assert(resource);
        auto size = sizeof(Target);
        auto align = alignof(Target);
        auto* buffer = resource->allocate(size, align);
        auto* target_ptr = new (buffer) Target(std::forward<Args&&>(args)...);
        return target_ptr;
    }

    template<class Target>
    void deallocate_ptr(actor_zeta::pmr::memory_resource* resource, Target** target) {
        assert(resource);
        assert(target);
        if (*target) {
            (*target)->~Target();
            resource->deallocate(*target, sizeof(Target));
            *target = nullptr;
        }
    }

    class deleter_t final {
    private:
        actor_zeta::pmr::memory_resource* resource_;

    public:
        explicit deleter_t(actor_zeta::pmr::memory_resource* resource)
            : resource_([](pmr::memory_resource* resource) {
                assert(resource);
                return resource;
            }(resource)) {}

        template<typename T>
        void operator()(T* target, std::size_t size = 1) {
            assert(target);
            for (std::size_t i = 0; i < size; ++i) {
                target[i].~T();
            }
            deallocate_ptr(resource_, &target);
        }
    };
}} // namespace actor_zeta