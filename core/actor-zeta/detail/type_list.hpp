#pragma once

#include <cstddef>
#include <type_traits>

namespace actor_zeta { namespace  type_traits {

// A list of types.
        template<class... Ts>
        struct type_list {
            constexpr type_list() = default;
        };

// size_t size(type_list)

/// Gets the number of template parameters of `List`.
        template<class List>
        struct type_list_size;

        template<class... Ts>
        struct type_list_size<type_list<Ts...>> {
            static constexpr size_t value = sizeof...(Ts);
        };

        template<class... Ts>
        constexpr size_t type_list_size<type_list<Ts...>>::value;

// type at(size_t)

        template<size_t N, class... E>
        struct type_list_at_impl;

        template<size_t N, typename E0, class... E>
        struct type_list_at_impl<N, E0, E...> {
            using type = typename type_list_at_impl<N - 1, E...>::type;
        };

        template<class E0, class... E>
        struct type_list_at_impl<0, E0, E...> {
            using type = E0;
        };


        template<class List, size_t N>
        struct type_list_at;

/// Gets element at index `N` of `List`.
        template<size_t N, class... E>
        struct type_list_at<type_list<E...>, N> {
            using type = typename type_list_at_impl<N, E...>::type;
        };

        template<class List, size_t N>
        using type_list_at_t = typename type_list_at<List, N>::type;


}}