#pragma once

#include <actor-zeta/detail/type_list.hpp>
#include <actor-zeta/detail/type_traits.hpp>
#include <functional>

namespace actor_zeta { namespace type_traits {

    template<class Functor>
    struct callable_trait;

    // good ol' function
    template<class R, class... Args>
    struct callable_trait<R(Args...)> {
        using result_type = R;
        using args_types = type_list<Args...>;
        using fun_sig = R(Args...);
        using fun_type = std::function<R(Args...)>;
        static constexpr size_t number_of_arguments = type_list_size<args_types>::value;
    };
    /*
        // member noexcept const function pointer
        template <class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...) const noexcept>: callable_trait<R(Ts...)> {};

// member noexcept function pointer
        template <class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...) noexcept> : callable_trait<R(Ts...)> {};

// member const function pointer
        template <class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...) const> : callable_trait<R (Ts...)> {};

// member function pointer
        template <class C, typename R, class... Ts>
        struct callable_trait<R (C::*)(Ts...)> : callable_trait<R (Ts...)> {};

// good ol' noexcept function pointer
        template <class R, class... Ts>
        struct callable_trait<R (*)(Ts...) noexcept> : callable_trait<R(Ts...)> {};

// good ol' function pointer
        template <class R, class... Ts>
        struct callable_trait<R (*)(Ts...)> : callable_trait<R (Ts...)> {};
*/

    // member const function pointer
    template<class C, typename R, class... Ts>
    struct callable_trait<R (C::*)(Ts...) const> : callable_trait<R(Ts...)> {
        using class_type = C;
    };

    // member function pointer
    template<class C, typename R, class... Ts>
    struct callable_trait<R (C::*)(Ts...)> : callable_trait<R(Ts...)> {
        using class_type = C;
    };

    // good ol' function pointer
    template<class R, class... Ts>
    struct callable_trait<R (*)(Ts...)> : callable_trait<R(Ts...)> {};

    template<class T>
    struct has_apply_operator final {
        template<class U>
        static auto sfinae(U*) -> decltype(&U::operator(), std::true_type());

        template<class U>
        static auto sfinae(...) -> std::false_type;

        using type = decltype(sfinae<T>(nullptr));
        static constexpr bool value = type::value;
    };

    // matches (IsFun || IsMemberFun)
    template<class T,
             bool IsFun = std::is_function<T>::value || std::is_function<typename std::remove_pointer<T>::type>::value || std::is_member_function_pointer<T>::value,
             bool HasApplyOp = has_apply_operator<T>::value>
    struct get_callable_trait_helper {
        using type = callable_trait<T>;
        using class_type = typename type::class_type;
        using result_type = typename type::result_type;
        using args_types = typename type::args_types;
        using fun_type = typename type::fun_type;
        using fun_sig = typename type::fun_sig;
        static constexpr size_t number_of_arguments = tl_size<args_types>::value;
    };

    // assume functor providing operator()
    template<class T>
    struct get_callable_trait_helper<T, false, true> {
        using type = callable_trait<decltype(&T::operator())>;
        using result_type = typename type::result_type;
        using args_types = typename type::args_types;
        using fun_type = typename type::fun_type;
        using fun_sig = typename type::fun_sig;
        static constexpr size_t number_of_arguments = tl_size<args_types>::value;
    };

    template<class T>
    struct get_callable_trait_helper<T, false, false> {};

    template<class T>
    struct get_callable_trait : get_callable_trait_helper<decay_t<T>> {};

    template<class T>
    using get_callable_trait_t = typename get_callable_trait<T>::type;

    template<class T>
    struct is_callable final {
        template<class C>
        static bool _fun(C*, typename get_callable_trait<C>::type* = nullptr);

        static void _fun(void*);

        using result_type = decltype(_fun(static_cast<decay_t<T>*>(nullptr)));
        static constexpr bool value = std::is_same<bool, result_type>::value;
    };

    template<class F, class... Ts>
    struct is_callable_with final {
        template<class U>
        static auto sfinae(U*) -> decltype((std::declval<U&>()) (std::declval<Ts>()...), std::true_type());

        template<class U>
        static auto sfinae(...) -> std::false_type;

        using type = decltype(sfinae<F>(nullptr));
        static constexpr bool value = type::value;
    };

}} // namespace actor_zeta::type_traits