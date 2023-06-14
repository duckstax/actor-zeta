#pragma once

#if CPP17_OR_GREATER and defined(__has_include)
#if __has_include(<memory_resource>)
#endif
#elif CPP14_OR_GREATER or CPP11_OR_GREATER

#include <actor-zeta/detail/type_traits.hpp>

#include <cassert>
#include <cstddef>
#include <new>
#include <utility>

#endif

namespace actor_zeta { namespace pmr {

#if CPP17_OR_GREATER and defined(__has_include)
#if __has_include(<memory_resource>)
#endif
#elif CPP14_OR_GREATER or CPP11_OR_GREATER

    template<class T>
    struct has_allocator_type {
    private:
        struct two {
            char lx;
            char lxx;
        };
        template<class Up>
        static two test(...);
        template<class Up>
        static char test(typename Up::allocator_type* = 0);

    public:
        static const bool value = sizeof(test<T>(0)) == 1;
    };

    template<typename Alloc, typename T>
    using is_erased_or_convertible = actor_zeta::type_traits::_or_<std::is_convertible<Alloc, T>, std::is_same<T, actor_zeta::type_traits::erased_type>>;

    template<typename T, typename Alloc, typename = actor_zeta::type_traits::void_t<>>
    struct uses_allocator_helper
        : std::false_type {};

    template<typename T, typename Alloc>
    struct uses_allocator_helper<T, Alloc, actor_zeta::type_traits::void_t<typename T::allocator_type>>
        : is_erased_or_convertible<Alloc, typename T::allocator_type>::type {};

    template<typename T, typename Alloc,
             bool = has_allocator_type<T>::value>
    struct uses_allocator_helper_wrapper
        : public std::false_type {};

    template<typename T, typename Alloc>
    struct uses_allocator_helper_wrapper<T, Alloc, true>
        : uses_allocator_helper<T, Alloc>::type {};

    template<typename T, typename Alloc>
    struct uses_allocator
        : uses_allocator_helper_wrapper<T, Alloc>::type {};

    struct uses_alloc_base {};

    struct uses_alloc_0 : uses_alloc_base {
        struct _Sink {
            void operator=(const void*) {}
        } a_;
    };

    template<typename Alloc>
    struct uses_alloc_1 : uses_alloc_base { const Alloc* a_; };

    template<typename Alloc>
    struct uses_alloc_2 : uses_alloc_base { const Alloc* a_; };

    template<bool, typename T, typename Alloc, typename... Args>
    struct uses_alloc;

    template<typename T, typename Alloc, typename... Args>
    struct uses_alloc<true, T, Alloc, Args...>
        : std::conditional<
              std::is_constructible<T, actor_zeta::type_traits::allocator_arg_t, const Alloc&, Args...>::value,
              uses_alloc_1<Alloc>,
              uses_alloc_2<Alloc>>::type {
        static_assert(actor_zeta::type_traits::_or_<
                          std::is_constructible<T, actor_zeta::type_traits::allocator_arg_t, const Alloc&, Args...>,
                          std::is_constructible<T, Args..., const Alloc&>>::value,
                      "construction with an allocator must be possible"
                      " if uses_allocator is true");
    };

    template<typename T, typename Alloc, typename... Args>
    struct uses_alloc<false, T, Alloc, Args...>
        : uses_alloc_0 {};

    template<
        typename T,
        typename Alloc,
        typename... Args>
    using uses_alloc_t = uses_alloc<uses_allocator<T, Alloc>::value, T, Alloc, Args...>;

    template<
        typename T,
        typename Alloc,
        typename... Args>
    inline uses_alloc_t<T, Alloc, Args...> use_alloc(const Alloc& a) {
        uses_alloc_t<T, Alloc, Args...> ret;
        ret.a_ = std::addressof(a);
        return ret;
    }

    template<
        typename T,
        typename Alloc,
        typename... _Args>
    void use_alloc(const Alloc&&) = delete;

    template<
        template<typename...> class Predicate,
        typename T,
        typename Alloc,
        typename... Args>
    struct is_uses_allocator_predicate
        : std::conditional<uses_allocator<T, Alloc>::value,
                           actor_zeta::type_traits::_or_<Predicate<T, actor_zeta::type_traits::allocator_arg_t, Alloc, Args...>,
                                             Predicate<T, Args..., Alloc>>,
                           Predicate<T, Args...>>::type {};

    template<typename T, typename Alloc, typename... Args>
    struct is_uses_allocator_constructible
        : is_uses_allocator_predicate<std::is_constructible, T, Alloc, Args...> {};

    template<typename T, typename Alloc, typename... Args>
    struct is_nothrow_uses_allocator_constructible
        : is_uses_allocator_predicate<std::is_nothrow_constructible, T, Alloc, Args...> {};

    template<typename T, typename... Args>
    void uses_allocator_construct_impl(uses_alloc_0 a, T* ptr, Args&&... args) {
        ::new ((void*) ptr) T(std::forward<Args>(args)...);
    }

    template<typename T, typename Alloc, typename... Args>
    void uses_allocator_construct_impl(uses_alloc_1<Alloc> a, T* ptr, Args&&... args) {
        ::new ((void*) ptr) T(actor_zeta::type_traits::allocator_arg, *a.a_, std::forward<Args>(args)...);
    }

    template<typename T, typename Alloc, typename... Args>
    void uses_allocator_construct_impl(uses_alloc_2<Alloc> a, T* ptr, Args&&... args) {
        ::new ((void*) ptr) T(std::forward<Args>(args)..., *a.a_);
    }

    template<typename T, typename Alloc, typename... Args>
    void uses_allocator_construct(const Alloc& a, T* ptr, Args&&... args) {
        uses_allocator_construct_impl(use_alloc<T, Alloc, Args...>(a), ptr, std::forward<Args>(args)...);
    }

#endif

}} // namespace actor_zeta::detail::pmr
