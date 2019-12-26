#pragma once

#include <functional>
#include <actor-zeta/detail/type_list.hpp>
#include <actor-zeta/detail/type_traits.hpp>

namespace actor_zeta { namespace  type_traits {

        template<class Functor>
        struct callable_trait;

/// good ol' function
        template<class R, class... Ts>
        struct callable_trait<R(Ts...)> {
            using result_type = R;
            using arg_types = type_list<Ts...>;
            using decayed_arg_types_in_a_tuple =  std::tuple<Ts...>; /// std::tuple<type_traits::decay_t<Ts>...>;
            using fun_sig = R(Ts...);
            using fun_type = std::function<R(Ts...)>;
        };

/// member const function pointer
        template<class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...) const> : callable_trait<R(Ts...)> {};

/// member function pointer
        template<class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...)> : callable_trait<R(Ts...)> {};

/// good ol' function pointer
        template<class R, class... Ts>
        struct callable_trait<R (*)(Ts...)> : callable_trait<R(Ts...)> {};

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
            using decayed_arg_types_in_a_tuple = typename type::decayed_arg_types_in_a_tuple ;
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
            using decayed_arg_types_in_a_tuple = typename type::decayed_arg_types_in_a_tuple ;
            static constexpr size_t num_args = type_list_size<arg_types>::value;
        };

        template<class T>
        struct get_callable_trait_helper<T, false, false> {};

        template<class T>
        struct get_callable_trait : get_callable_trait_helper<decay_t<T>> {};


        template<typename C, typename T, typename U>
        using is_callable_t = decltype(std::declval<C &>()(std::declval<T>(), std::declval<U>()));

        template<typename C, typename T, typename U>
        using is_callable = is_detected<is_callable_t, C, T, U>;


}}