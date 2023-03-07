#pragma once

#include <cstdlib>

#include <vector>
#include <map>
#include <set>
#include <unordered_map>

#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>

namespace actor_zeta { namespace base {

    /**
     * @enum class actor_type_e
     * @brief 
     */
    enum class actor_type_e : int8_t {
        PMR,
    };

    /** 
     * @class actor_traits
     * @brief 
     * 
     * @tparam actor_type 
     */
    template<actor_type_e actor_type>
    class actor_traits {};

    /**
     * @class actor_traits
     * @brief 
     * 
     * @tparam actor_type==actor_type_e::PMR
     */
    template<>
    class actor_traits<actor_type_e::PMR> {
        /**
         * @brief polymorphic_allocator
         * 
         * @tparam T 
         */
        template<class T>
        using polymorphic_allocator = actor_zeta::detail::pmr::polymorphic_allocator<T>;

        /**
         * @brief basic_string_type
         * 
         * @tparam CharT 
         * @tparam Traits 
         */
        template<class CharT, class Traits = std::char_traits<CharT>>
        using basic_string_type = std::basic_string<CharT, Traits, polymorphic_allocator<CharT>>;
    
    public:
        /**
         * @brief memory_resource
         * 
         */
        using memory_resource = actor_zeta::detail::pmr::memory_resource;
        /**
         * @brief memory_resource_ptr
         * 
         */
        using memory_resource_ptr = memory_resource*;

        /**
         * @brief vector_type
         * 
         * @tparam T 
         */
        template<class T>
        using vector_type = std::vector<T, polymorphic_allocator<T>>;

        /**
         * @brief set_type
         * 
         * @tparam T 
         */
        template<class T>
        using set_type = std::set<T, std::less<T>, polymorphic_allocator<T>>;

        /**
         * @brief map_type
         * 
         * @tparam Key 
         * @tparam T 
         * @tparam Compare 
         */
        template<class Key, class T, class Compare = std::less<Key>>
        using map_type = std::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T>>>;

        /**
         * @brief unordered_map_type
         * 
         * @tparam Key 
         * @tparam T 
         * @tparam Hash 
         * @tparam KeyEqual 
         */
        template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
        using unordered_map_type = std::unordered_map<Key, T, Hash, KeyEqual, polymorphic_allocator<std::pair<const Key,T>>>;

        /**
         * @brief string_type
         */
        using string_type = basic_string_type<char>;

        /**
         * @brief deleter_type
         * 
         * @tparam T 
         */
        template<typename T>
        using deleter_type = actor_zeta::detail::deleter_t<T>;

        /**
         * @brief unique_ptr_type
         * 
         * @tparam T 
         */
        template<typename T>
        using unique_ptr_type = std::unique_ptr<T, deleter_type<T>>;
    };

} }
