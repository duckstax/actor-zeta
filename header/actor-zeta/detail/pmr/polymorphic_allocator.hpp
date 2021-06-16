#pragma once

#if CPP17_OR_GREATER

#elif CPP14_OR_GREATER or CPP11_OR_GREATER

#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/detail/pmr/new_allocator.hpp>
#include <cassert>
#include <cstddef>
#include <utility>

#endif

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP17_OR_GREATER

#elif CPP14_OR_GREATER or CPP11_OR_GREATER
    template<class T>
    class polymorphic_allocator {
    public:
        using value_type = T;

        /// non C++ 17 std
        polymorphic_allocator() noexcept = delete;

        polymorphic_allocator(memory_resource* r) noexcept
            : resource_(r) { assert(r != 0); }

        polymorphic_allocator(const polymorphic_allocator& other) noexcept
            : resource_(other.resource_) {}

        template<class U>
        polymorphic_allocator(const polymorphic_allocator<U>& other) noexcept
            : resource_(other.resource()) {}

        polymorphic_allocator& operator=(const polymorphic_allocator& other) noexcept {
            resource_ = other.resource_;
            return *this;
        }

        T* allocate(size_t n) {
            return static_cast<T*>(resource_->allocate(n * sizeof(T), alignof(T));
        }

        void deallocate(T* p, size_t n) noexcept { resource_->deallocate(p, n * sizeof(T), alignof(T)); }

        template<typename U, class... Args>
        void construct(U* p, Args&&... args) {
            new_allocator<U> na;
            dispatch_uses_allocator(na, *this, p, std::forward<Args>(args)...);
        }

        template<class U>
        void destroy(U* p) {
            (void) p;
            p->~U();
        }

        /// non C++ 17 std
        /// polymorphic_allocator select_on_container_copy_construction() const noexcept { return polymorphic_allocator(); }

        memory_resource* resource() const noexcept { return resource_; }

    private:
        memory_resource* resource_;
    };

    template<class T1, class T2>
    bool operator==(const polymorphic_allocator<T1>& a, const polymorphic_allocator<T2>& b) noexcept { return *a.resource() == *b.resource(); }

    template<class T1, class T2>
    bool operator!=(const polymorphic_allocator<T1>& a, const polymorphic_allocator<T2>& b) noexcept { return *a.resource() != *b.resource(); }

#endif

}}} // namespace actor_zeta::detail::pmr
