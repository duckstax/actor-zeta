#pragma once

// clang-format off
#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
// clang-format on

namespace actor_zeta { namespace detail { namespace pmr {

    template<class Target, class... Args>
    Target* allocate_ptr(memory_resource* memory_resource, Args&&... args) {
        assert(memory_resource);
        auto size = sizeof(Target);
        auto align = alignof(Target);
        auto* buffer = memory_resource->allocate(size, align);
        auto* target_ptr = new (buffer) Target(std::forward<Args&&>(args)...);
        return target_ptr;
    }

    template<class Target>
    void deallocate_ptr(memory_resource* memory_resource, Target** target) {
        assert(memory_resource);
        assert(target);
        if (*target) {
            (*target)->~Target();
            memory_resource->deallocate(*target, sizeof(Target));
            *target = nullptr;
        }
    }

    class memory_resource_base {
        memory_resource* memory_resource_ = nullptr;

    protected:
        explicit memory_resource_base(memory_resource* memory_resource)
            : memory_resource_(memory_resource ? memory_resource : get_default_resource()) {
            assert(memory_resource_);
        }
        virtual ~memory_resource_base() = default;


        inline auto resource() const -> memory_resource* {
            return memory_resource_;
        }

        template<class Target, class... Args>
        Target* allocate_ptr(Args&&... args) {
            return actor_zeta::detail::pmr::allocate_ptr<Target, Args...>(resource(), std::forward<Args&&>(args)...);
        }

        template<class Target>
        void deallocate_ptr(Target** target) {
            actor_zeta::detail::pmr::deallocate_ptr<Target>(resource(), target);
        }
    };

    template<typename Tp_, typename _Alloc = std::allocator<Tp_>>
    class deleter_t final : public std::allocator_traits<_Alloc> {
    public:
        void operator()(Tp_* target, std::size_t size = 1) {
            for (int i = 0; i < size; ++i) {
                destroy(&target[i]);
            }
            deallocate(target, sizeof(Tp_) * size);
        }
    };

}}}
