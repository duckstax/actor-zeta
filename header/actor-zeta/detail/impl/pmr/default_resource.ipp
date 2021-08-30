#pragma once

#include <actor-zeta/detail/pmr/default_resource.hpp>

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP17_OR_GREATER
// nothing
#elif CPP14_OR_GREATER or CPP11_OR_GREATER

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
    REQUIRE_CONST_INIT
    null_memory_resource::holder
        null_memory_resource::instance_;
#else
    REQUIRE_CONST_INIT
    null_memory_resource
        null_memory_resource::instance_;
#endif
#endif

    null_memory_resource::
        ~null_memory_resource() = default;

    void*
    null_memory_resource::do_allocate(
        std::size_t bytes,
        std::size_t alignment) {
        assert(false);
    }

    void
    null_memory_resource::do_deallocate(
        void* p,
        std::size_t bytes,
        std::size_t alignment) {}

    bool
    null_memory_resource::do_is_equal(
        memory_resource const& mr) const noexcept {
        return &mr == this;
    }

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
    REQUIRE_CONST_INIT
    default_memory_resource::holder
        default_memory_resource::instance_;
#else
    REQUIRE_CONST_INIT
    default_memory_resource
        default_memory_resource::instance_;
#endif
#endif

    default_memory_resource::
        ~default_memory_resource() = default;

    constexpr bool is_pow2(size_t n) { return (0 == (n & (n - 1))); }

    template<typename Alloc>
    void* aligned_allocate(size_t bytes, size_t alignment, Alloc alloc) {
        assert(is_pow2(alignment));

        size_t padded_allocation_size{bytes + alignment + sizeof(std::ptrdiff_t)};

        char* const original = static_cast<char*>(alloc(padded_allocation_size));

        void* aligned{original + sizeof(std::ptrdiff_t)};

        std::align(alignment, bytes, aligned, padded_allocation_size);

        std::ptrdiff_t offset = static_cast<char*>(aligned) - original;

        *(static_cast<std::ptrdiff_t*>(aligned) - 1) = offset;

        return aligned;
    }

    template<typename Dealloc>
    void aligned_deallocate(void* p, size_t bytes, size_t alignment, Dealloc dealloc) {
        (void) alignment;
        (void) bytes;

        std::ptrdiff_t const offset = *(reinterpret_cast<std::ptrdiff_t*>(p) - 1);

        void* const original = static_cast<char*>(p) - offset;

        dealloc(original);
    }

    void*
    default_memory_resource::
        do_allocate(
            std::size_t bytes,
            std::size_t alignment) {
        return aligned_allocate(bytes, alignment, [](size_t size) { return ::operator new(size); });
    }

    void
    default_memory_resource::
        do_deallocate(
            void* p,
            std::size_t bytes,
            std::size_t alignment) {
        aligned_deallocate(p, bytes, alignment, [](void* p) { ::operator delete(p); });
    }

    bool
    default_memory_resource::
        do_is_equal(
            memory_resource const& mr) const noexcept {
        return this == &mr;
    }

#endif

}}} // namespace actor_zeta::detail::pmr