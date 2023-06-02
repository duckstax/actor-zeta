#pragma once

#include <actor-zeta/config.hpp>

#if CPP17_OR_GREATER
#if __has_include(<memory_resource>)
#include <memory_resource>
namespace actor_zeta { namespace pmr {
    using std::pmr::memory_resource;
}} // namespace actor_zeta::pmr
#elif __has_include(<experimental/memory_resource>)
// clang-format off
#include <actor-zeta/detail/pmr/memory_resource.hpp>
// clang-format on
#endif
#elif CPP14_OR_GREATER || CPP11_OR_GREATER
// clang-format off
#include <actor-zeta/detail/pmr/memory_resource.hpp>
// clang-format on
#endif

#if CPP17_OR_GREATER
#if __has_include(<memory_resource>)
namespace actor_zeta { namespace pmr {
    template<class T>
    using polymorphic_allocator = std::pmr::polymorphic_allocator<T>;

    using std::pmr::get_default_resource;
    using std::pmr::new_delete_resource;
    using std::pmr::null_memory_resource;
    using std::pmr::set_default_resource;
}} // namespace actor_zeta::pmr
#elif __has_include(<experimental/memory_resource>)
#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>
#endif
#elif CPP14_OR_GREATER || CPP11_OR_GREATER
#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>
#endif