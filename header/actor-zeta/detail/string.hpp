#pragma once

#include <string>

#include "actor-zeta/config.hpp"
#include "actor-zeta/detail/memory_resource.hpp"

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP17_OR_GREATER

#if __has_include(<memory_resource>)

    template<
        typename Char,
        typename Traits = std::char_traits<Char>>
    using basic_string = std::pmr::basic_string<T>;

#else

    template<
        typename Char,
        typename Traits = std::char_traits<Char>>
    using basic_string = std::pmr::experimental::basic_string<T>;

#endif

#elif CPP14_OR_GREATER or CPP11_OR_GREATER

    template<
        typename Char,
        typename Traits = std::char_traits<Char>>
    using basic_string = std::basic_string<Char, actor_zeta::detail::pmr::polymorphic_allocator<Char>>;

#endif

    using string = basic_string<char>;

}}} // namespace actor_zeta::detail::pmr