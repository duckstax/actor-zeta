#pragma once

#include <actor-zeta/config.hpp>

#if HAVE_STD_PMR==1

#include <memory_resource>

namespace actor_zeta { namespace pmr {

    using std::pmr::memory_resource;

}} // namespace actor_zeta::pmr

namespace actor_zeta { namespace pmr {

    template<class T>
    using polymorphic_allocator = std::pmr::polymorphic_allocator<T>;

    using std::pmr::get_default_resource;
    using std::pmr::new_delete_resource;
    using std::pmr::null_memory_resource;
    using std::pmr::set_default_resource;

}} // namespace actor_zeta::pmr

#else

// clang-format off
#include <actor-zeta/detail/pmr/memory_resource.hpp>
// clang-format on

#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>

#endif