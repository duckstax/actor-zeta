#pragma once

#include <iterator>

namespace actor_zeta {
    namespace type_traits {

        template<class... Ts>
        using void_t = void;

        template<class T>
        struct identity {
            using type = T;
        };

        template<
                class T,
                class Void,
                template<class...> class,
                class...
        >
        struct detector : identity<T> {
            using value_t = std::false_type;
        };

        template<
                class T,
                template<class...> class U,
                class... Args
        >
        struct detector<T, void_t<U<Args...>>, U, Args...> : identity<U<Args...>> {
            using value_t = std::true_type;
        };

        struct none_such final {
            none_such(none_such const &) = delete;

            none_such() = delete;

            ~none_such() = delete;

            void operator=(none_such const &) = delete;
        };

        template<class T, template<class...> class U, class... Args>
        using detected_or = detector<T, void, U, Args...>;

        template<template<class...> class T, class... Args>
        using detected_t = typename detected_or<none_such, T, Args...>::type;

        template<class T, template<class...> class U, class... Args>
        using detected_or_t = typename detected_or<T, U, Args...>::type;

        template<template<class...> class T, class... Args>
        using is_detected = typename detected_or<none_such, T, Args...>::value_t;

        template<class To, template<class...> class T, class... Args>
        using is_detected_convertible = std::is_convertible<detected_t<T, Args...>, To>;

        template<class T, template<class...> class U, class... Args>
        using is_detected_exact = std::is_same<T, detected_t<U, Args...>>;

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

        template<typename...>
        struct __or__;

        template<>
        struct __or__<> : public std::false_type {
        };

        template<typename B1>
        struct __or__<B1> : public B1 {
        };

        template<typename B1, typename B2>
        struct __or__<B1, B2> : public std::conditional<B1::value, B1, B2>::type {
        };

        template<typename B1, typename B2, typename B3, typename... Bn>
        struct __or__<B1, B2, B3, Bn...> : public std::conditional<B1::value, B1, __or__<B2, B3, Bn...>>::type {
        };

        template<typename... Bn>
        struct disjunction : __or__<Bn...> {
        };

        //template<typename... Bn>
        //inline constexpr bool disjunction_v = disjunction<Bn...>::value;

        template<class _Tp>
        using add_pointer_t = typename std::add_pointer<_Tp>::type;

    }
}