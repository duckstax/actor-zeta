#pragma once

#include <iterator>

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

//// C++ 14
        template<bool _Cond, typename _Tp = void>
        using enable_if_t = typename std::enable_if<_Cond, _Tp>::type;

        template<class T>
        using decay_t = typename std::decay<T>::type;

        template<bool __v>
        using bool_constant = std::integral_constant<bool, __v>;

        template<std::size_t _Len>
        struct __aligned_storage_msa{
            union __type{
                unsigned char __data[_Len];
                struct __attribute__((__aligned__)) { } __align;
            };
        };

        template<size_t _Len, size_t _Align =__alignof__(typename __aligned_storage_msa<_Len>::__type)>
        using aligned_storage_t = typename std::aligned_storage<_Len, _Align>::type;

/// C++ 17

        namespace detail {
            struct in_place_tag {};
            template <class> struct in_place_type_tag {};
            template <size_t> struct in_place_index_tag {};
        }

        struct in_place_tag {
            in_place_tag() = delete;

        private:
            explicit in_place_tag(detail::in_place_tag) {}
            friend inline in_place_tag internal_construct_in_place_tag();
        };

        // internal factory function for in_place_tag
        inline in_place_tag internal_construct_in_place_tag() { return in_place_tag(detail::in_place_tag{}); }

        using in_place_t = in_place_tag(&)(detail::in_place_tag);

        template <class T>
        using in_place_type_t = in_place_tag(&)(detail::in_place_type_tag<T>);

        template <size_t N>
        using in_place_index_t = in_place_tag(&)(detail::in_place_index_tag<N>);


        inline in_place_tag in_place(detail::in_place_tag) { return internal_construct_in_place_tag(); }

        template <class T>
        inline in_place_tag in_place(detail::in_place_type_tag<T>) { return internal_construct_in_place_tag(); }

        template <std::size_t I>
        inline in_place_tag in_place(detail::in_place_index_tag<I>) { return internal_construct_in_place_tag(); }

}}