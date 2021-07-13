#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "polymorphic_allocator.hpp"

namespace actor_zeta { namespace detail { namespace pmr {

    template<typename T>
    using vector = std::vector<T, polymorphic_allocator<T>>;

    template<typename Char, typename Traits = std::char_traits<_CharT>>
    using basic_string = std::basic_string<Char, Traits, polymorphic_allocator<Char>>;

    using string = basic_string<char>;

    template<
        typename Key,
        typename T,
        typename Hash = std::hash<Key>,
        typename Pred = std::equal_to<Key>>
    using unordered_map = std::unordered_map<Key, T, Hash, Pred, polymorphic_allocator<std::pair<const Key, T>>>;

}}} // namespace actor_zeta::detail::pmr