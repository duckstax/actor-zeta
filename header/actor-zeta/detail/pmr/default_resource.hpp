#pragma once

#include <actor-zeta/config.hpp>
#include <actor-zeta/detail/pmr/mempry_resource.hpp>
#include <new>

namespace actor_zeta { namespace detail { namespace pmr {

class default_resource final : public memory_resource {
    union holder;

#ifndef WEAK_CONSTINIT
# ifndef NO_DESTROY
    static holder instance_;
# else
    NO_DESTROY
    static default_resource instance_;
# endif
#endif

public:
    static
    memory_resource*
    get() noexcept {
    #ifdef WEAK_CONSTINIT
        static default_resource instance_;
    #endif
        return reinterpret_cast<memory_resource*>(
            reinterpret_cast<std::uintptr_t*>(
                &instance_));
    }
    
    ~default_resource();

    void*
    do_allocate(
        std::size_t n,
        std::size_t) override;

    void
    do_deallocate(
        void* p,
        std::size_t,
        std::size_t) override;

    bool
    do_is_equal(
        memory_resource const& mr) const noexcept override;
};

union default_resource::holder {
#ifndef WEAK_CONSTINIT
    constexpr
#endif
    holder(): mr(){}
    ~holder(){}

    default_resource mr;
};

}}}