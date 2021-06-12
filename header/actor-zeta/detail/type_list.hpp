#pragma once

#include <cstddef>
#include <type_traits>

namespace actor_zeta { namespace type_traits {

    struct unit_t final {
        constexpr unit_t() noexcept {}

        constexpr unit_t(const unit_t&) noexcept {}

        template<class T>
        explicit constexpr unit_t(T&&) noexcept {}

        template<class... Ts>
        constexpr unit_t operator()(Ts&&...) const noexcept {
            return {};
        }
    };

    // A list of types.
    template<class... Ts>
    struct type_list {
        constexpr type_list() = default;
    };

    using empty_type_list = type_list<>;

    template<class T>
    struct is_type_list {
        static constexpr bool value = false;
    };

    template<class... Ts>
    struct is_type_list<type_list<Ts...>> {
        static constexpr bool value = true;
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

    /// Gets the first element of `List`.
    template<class List>
    struct tl_head;

    template<>
    struct tl_head<type_list<>> {
        using type = void;
    };

    template<typename T0, class... Ts>
    struct tl_head<type_list<T0, Ts...>> {
        using type = T0;
    };

    template<class List>
    using tl_head_t = typename tl_head<List>::type;

    template<class List>
    struct tl_tail;

    template<>
    struct tl_tail<type_list<>> {
        using type = type_list<>;
    };

    template<typename T0, class... Ts>
    struct tl_tail<type_list<T0, Ts...>> {
        using type = type_list<Ts...>;
    };

    template<class List>
    using tl_tail_t = typename tl_tail<List>::type;

    template<class List>
    struct tl_size;

    template<class... Ts>
    struct tl_size<type_list<Ts...>> {
        static constexpr size_t value = sizeof...(Ts);
    };

    template<class... Ts>
    constexpr size_t tl_size<type_list<Ts...>>::value;

    // list slice(size_t, size_t)

    template<size_t LeftOffset, size_t Remaining, typename PadType, class List, class... Ts>
    struct tl_slice_impl {
        using type = typename tl_slice_impl<LeftOffset - 1, Remaining, PadType,
                                            tl_tail_t<List>, Ts...>::type;
    };

    template<size_t Remaining, typename PadType, class List, class... Ts>
    struct tl_slice_impl<0, Remaining, PadType, List, Ts...> {
        using type =
            typename tl_slice_impl<0, Remaining - 1, PadType, tl_tail_t<List>, Ts...,
                                   tl_head_t<List>>::type;
    };

    template<size_t Remaining, typename PadType, class... Ts>
    struct tl_slice_impl<0, Remaining, PadType, empty_type_list, Ts...> {
        using type = typename tl_slice_impl<0, Remaining - 1, PadType,
                                            empty_type_list, Ts..., PadType>::type;
    };

    template<class PadType, class List, class... T>
    struct tl_slice_impl<0, 0, PadType, List, T...> {
        using type = type_list<T...>;
    };

    template<class PadType, class... T>
    struct tl_slice_impl<0, 0, PadType, empty_type_list, T...> {
        using type = type_list<T...>;
    };

    template<class List, size_t ListSize, size_t First, size_t Last, typename PadType = unit_t>
    struct tl_slice_ {
        using type =
            typename tl_slice_impl<First, (Last - First), PadType, List>::type;
    };

    template<class List, size_t ListSize, typename PadType>
    struct tl_slice_<List, ListSize, 0, ListSize, PadType> {
        using type = List;
    };

    /// Creates a new list from range (First, Last].
    template<class List, size_t First, size_t Last>
    struct tl_slice {
        using type = typename tl_slice_<List, tl_size<List>::value,
                                        (First > Last ? Last : First), Last>::type;
    };

    template<class List, size_t First, size_t Last>
    using tl_slice_t = typename tl_slice<List, First, Last>::type;

}} // namespace actor_zeta::type_traits