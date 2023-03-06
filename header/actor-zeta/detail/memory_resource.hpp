#pragma once

// clang-format off
#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
// clang-format on

namespace actor_zeta { namespace pmr {
    using detail::pmr::get_default_resource;
    using detail::pmr::set_default_resource;
    using detail::pmr::new_delete_resource;
    using detail::pmr::null_memory_resource;
    using detail::pmr::polymorphic_allocator;
    using detail::pmr::memory_resource;
}} // namespace actor_zeta::pmr