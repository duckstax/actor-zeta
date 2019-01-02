#pragma once

namespace actor_zeta { namespace  type_traits {

        template<class... Ts>
        using void_t = void;

        namespace detail {
            template<template<class...> class Trait, class Enabler, class... Args>
            struct is_detected : std::false_type {
            };

            template<template<class...> class Trait, class... Args>
            struct is_detected<Trait, void_t<Trait<Args...>>, Args...> : std::true_type {
            };
        }

        template<template<class...> class Trait, class... Args>
        using is_detected = typename detail::is_detected<Trait, void, Args...>::type;

        template<typename T, typename U>
        using equal_compare_t = decltype(std::declval<const T &>() == std::declval<const U &>());

        template<typename T, typename U>
        using are_equal_comparable = is_detected<equal_compare_t, T, U>;

        template<typename I>
        using is_input_iterator= typename std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<I>::iterator_category>::type;

        template<bool _Cond, typename _Tp = void>
        using enable_if_t = typename std::enable_if<_Cond, _Tp>::type;

        template<class T>
        using decay_t = typename std::decay<T>::type;

}}