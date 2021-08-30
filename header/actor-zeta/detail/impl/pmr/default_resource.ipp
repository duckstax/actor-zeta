#pragma once

#include <actor-zeta/detail/pmr/default_resource.hpp>

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP14_OR_GREATER or CPP11_OR_GREATER

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

    void*
    default_memory_resource::
        do_allocate(
            std::size_t n,
            std::size_t) {
        return ::operator new(n);
    }

    void
    default_memory_resource::
        do_deallocate(
            void* p,
            std::size_t,
            std::size_t) {
        ::operator delete(p);
    }

    bool
    default_memory_resource::
        do_is_equal(
            memory_resource const& mr) const noexcept {
        return this == &mr;
    }

#endif

}}} // namespace actor_zeta::detail::pmr