#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>

#ifdef __GNUC__
#include <features.h>
#endif

namespace actor_zeta { namespace detail {

    static constexpr std::size_t DEFAULT_ALIGNMENT{alignof(::max_align_t)};

    constexpr bool is_pow2(std::size_t n) { return (0 == (n & (n - 1))); }

    constexpr bool is_supported_alignment(std::size_t alignment) { return is_pow2(alignment); }

    void* align(std::size_t alignment, std::size_t size, void*& ptr, std::size_t& space) {
#ifdef __GNUC__
#if __GNUC_PREREQ(5, 0)
        //      If  gcc_version >= 5.0
        return std::align(alignment, size, ptr, space);
#elif __GNUC_PREREQ(4, 0)
        //       If gcc_version >= 4.0
        auto pn = reinterpret_cast<std::size_t>(ptr);
        auto aligned = (pn + alignment - 1) & -alignment;
        auto new_space = space - (aligned - pn);
        if (new_space < size)
            return nullptr;
        space = new_space;
        return ptr = reinterpret_cast<void*>(aligned);

#else
        //       Else
        return std::align(alignment, size, ptr, space);
#endif
#else
        //    If not gcc
        return std::align(alignment, size, ptr, space);
#endif
    }

    template<typename Alloc>
    void* aligned_allocate(std::size_t bytes, std::size_t alignment, Alloc alloc) {
        assert(is_pow2(alignment));

        std::size_t padded_allocation_size{bytes + alignment + sizeof(std::ptrdiff_t)};

        char* const original = static_cast<char*>(alloc(padded_allocation_size));

        void* aligned{original + sizeof(std::ptrdiff_t)};

        align(alignment, bytes, aligned, padded_allocation_size);

        std::ptrdiff_t offset = static_cast<char*>(aligned) - original;

        *(static_cast<std::ptrdiff_t*>(aligned) - 1) = offset;

        return aligned;
    }

    template<typename Dealloc>
    void aligned_deallocate(void* p, std::size_t bytes, std::size_t alignment, Dealloc dealloc) {
        (void) alignment;
        (void) bytes;

        std::ptrdiff_t const offset = *(reinterpret_cast<std::ptrdiff_t*>(p) - 1);

        void* const original = static_cast<char*>(p) - offset;

        dealloc(original);
    }

}

} // namespace actor_zeta::detail
