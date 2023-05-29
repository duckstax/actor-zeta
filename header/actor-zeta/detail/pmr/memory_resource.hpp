#pragma once

#include <actor-zeta/config.hpp>
#include <cstddef>
#include <cstdio>

#if CPP17_OR_GREATER && defined __has_include  && __has_include(<memory_resource>)
#include <memory_resource>
#endif

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP17_OR_GREATER && defined __has_include  && __has_include(<memory_resource>)
    using std::pmr::memory_resource;
#else

    class memory_resource {
    public:
        virtual ~memory_resource() {}

        void* allocate(std::size_t bytes, std::size_t alignment = alignof(::max_align_t)) {
            return this->do_allocate(bytes, alignment);
        }

        void deallocate(void* p, std::size_t bytes, std::size_t alignment = alignof(::max_align_t)) {
            return this->do_deallocate(p, bytes, alignment);
        }

        bool is_equal(const memory_resource& other) const noexcept {
            return this->do_is_equal(other);
        }

    protected:
        virtual void* do_allocate(std::size_t bytes, std::size_t alignment) = 0;

        virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) = 0;

        virtual bool do_is_equal(const memory_resource& other) const noexcept = 0;
    };

    inline bool operator==(const memory_resource& a, const memory_resource& b) noexcept {
        return &a == &b || a.is_equal(b);
    }

    inline bool operator!=(const memory_resource& a, const memory_resource& b) noexcept {
        return !(a == b);
    }

#endif

}}} // namespace actor_zeta::detail::pmr
