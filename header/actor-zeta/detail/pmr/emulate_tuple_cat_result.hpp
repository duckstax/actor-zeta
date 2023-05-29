#pragma once

#include <actor-zeta/config.hpp>

#include <actor-zeta/detail/type_traits.hpp>

#include <cassert>
#include <cstddef>

#include <new>
#include <tuple>
#include <utility>

namespace actor_zeta { namespace detail { namespace pmr {

    template<std::size_t i, typename _Tp>
    using tuple_element_t = typename std::tuple_element<i, _Tp>::type;

    template<size_t, typename, typename, size_t>
    struct make_tuple_impl;

    template<size_t Idx, typename Tuple, typename... T, size_t Nm>
    struct make_tuple_impl<Idx, std::tuple<T...>, Tuple, Nm>
        : make_tuple_impl<Idx + 1, std::tuple<T..., tuple_element_t<Idx, Tuple>>, Tuple, Nm> {};

    template<std::size_t Nm, typename Tuple, typename... T>
    struct make_tuple_impl<Nm, std::tuple<T...>, Tuple, Nm> {
        using type = std::tuple<T...>;
    };

    template<typename Tuple>
    struct do_make_tuple
        : make_tuple_impl<0, std::tuple<>, Tuple, std::tuple_size<Tuple>::value> {};

    template<typename Tuple>
    struct make_tuple
        : public do_make_tuple<type_traits::remove_cvref_t<Tuple>> {};

    template<typename...>
    struct combine_tuples;

    template<>
    struct combine_tuples<> {
        using type = std::tuple<>;
    };

    template<typename... T>
    struct combine_tuples<std::tuple<T...>> {
        using type = std::tuple<T...>;
    };

    template<typename... T1, typename... T2, typename... Rem>
    struct combine_tuples<std::tuple<T1...>, std::tuple<T2...>, Rem...> {
        using type = typename combine_tuples<std::tuple<T1..., T2...>,
                                             Rem...>::type;
    };

    template<typename... Args>
    struct tuple_cat_result {
        using type = typename combine_tuples<typename make_tuple<Args>::type...>::type;
    };

}}} // namespace actor_zeta::detail::pmr
