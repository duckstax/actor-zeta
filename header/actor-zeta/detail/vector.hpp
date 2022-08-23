#pragma once

#include <vector>

#include "actor-zeta/config.hpp"
#include "actor-zeta/detail/memory_resource.hpp"

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP17_OR_GREATER

#if __has_include(<memory_resource>)

    template<class T>
    using vector = std::pmr::vector<T>;

#else

    template<class T>
    using vector = std::pmr::experimental::vector<T>;

#endif

#elif CPP14_OR_GREATER or CPP11_OR_GREATER

    template<class T>
    using vector = std::vector<T, actor_zeta::detail::pmr::polymorphic_allocator<T>>;

#endif

}}} // namespace actor_zeta::detail::pmr