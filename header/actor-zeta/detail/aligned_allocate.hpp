#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>

namespace actor_zeta { namespace detail {

    static constexpr std::size_t DEFAULT_ALIGNMENT{alignof(::max_align_t)};

    constexpr inline bool is_pow2(std::size_t n) { return (0 == (n & (n - 1))); }

    constexpr inline bool is_supported_alignment(std::size_t alignment) { return is_pow2(alignment); }

    void* align(std::size_t alignment, std::size_t size, void*& ptr, std::size_t& space);

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
