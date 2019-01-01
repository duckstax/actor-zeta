#pragma once

#include <functional>
#include "type_list.h"

namespace actor_zeta { namespace  type_traits {

        template<bool _Cond, typename _Tp = void>
        using enable_if_t = typename std::enable_if<_Cond, _Tp>::type;

        template<class T>
        using decay_t = typename std::decay<T>::type;

        template<class Functor>
        struct callable_trait;

/// good ol' function
        template<class R, class... Ts>
        struct callable_trait<R(Ts...)> {
            using result_type = R;
            using arg_types = type_list<Ts...>;
            using fun_sig = R(Ts...);
            using fun_type = std::function<R(Ts...)>;
        };

/// member const function pointer
        template<class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...) const> : callable_trait<R(Ts...)> {
        };

/// member function pointer
        template<class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...)> : callable_trait<R(Ts...)> {
        };

/// good ol' function pointer
        template<class R, class... Ts>
        struct callable_trait<R (*)(Ts...)> : callable_trait<R(Ts...)> {
        };

        template<class T>
        struct has_apply_operator {
            template<class U>
            static auto sfinae(U *) -> decltype(&U::operator(), std::true_type());

            template<class U>
            static auto sfinae(...) -> std::false_type;

            using type = decltype(sfinae<T>(nullptr));
            static constexpr bool value = type::value;
        };

/// matches (IsFun || IsMemberFun)
        template<class T,
                bool IsFun = std::is_function<T>::value
                             || std::is_function<
                        typename std::remove_pointer<T>::type
                >::value
                             || std::is_member_function_pointer<T>::value,
                bool HasApplyOp = has_apply_operator<T>::value>
        struct get_callable_trait_helper {
            using type = callable_trait<T>;
            using result_type = typename type::result_type;
            using arg_types = typename type::arg_types;
            using fun_type = typename type::fun_type;
            using fun_sig = typename type::fun_sig;
            static constexpr size_t num_args = type_list_size<arg_types>::value;
        };

/// assume functor providing operator()
        template<class T>
        struct get_callable_trait_helper<T, false, true> {
            using type = callable_trait<decltype(&T::operator())>;
            using result_type = typename type::result_type;
            using arg_types = typename type::arg_types;
            using fun_type = typename type::fun_type;
            using fun_sig = typename type::fun_sig;
            static constexpr size_t num_args = type_list_size<arg_types>::value;
        };

        template<class T>
        struct get_callable_trait_helper<T, false, false> {
        };

        template<class T>
        struct get_callable_trait : get_callable_trait_helper<decay_t<T>> {
        };

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

        template<typename C, typename T, typename U>
        using is_callable_t = decltype(std::declval<C &>()(std::declval<T>(), std::declval<U>()));

        template<typename C, typename T, typename U>
        using is_callable = is_detected<is_callable_t, C, T, U>;


    }}