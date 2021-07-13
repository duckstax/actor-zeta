#pragma once

#include <actor-zeta/detail/pmr/default_resource.hpp>

namespace actor_zeta { namespace detail { namespace pmr {

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
    REQUIRE_CONST_INIT
    default_resource::holder
        default_resource::instance_;
#else
    REQUIRE_CONST_INIT
    default_resource
        default_resource::instance_;
#endif
#endif

    default_resource::
        ~default_resource() = default;

    void*
    default_resource::
        do_allocate(
            std::size_t n,
            std::size_t) {
        return ::operator new(n);
    }

    void
    default_resource::
        do_deallocate(
            void* p,
            std::size_t,
            std::size_t) {
        ::operator delete(p);
    }

    bool
    default_resource::
        do_is_equal(
            memory_resource const& mr) const noexcept {
        return this == &mr;
    }

}}} // namespace actor_zeta::detail::pmr