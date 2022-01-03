#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/type_list.hpp>
#include <actor-zeta/detail/type_traits.hpp>

namespace actor_zeta { namespace base {
    // clang-format off
        template <class List, std::size_t I>
        using forward_arg =
        typename std::conditional<std::is_lvalue_reference<type_traits::type_list_at_t<List, I>>::value,
        typename std::add_lvalue_reference<type_traits::decay_t<type_traits::type_list_at_t<List, I>>>::type,
        typename std::add_rvalue_reference<type_traits::decay_t<type_traits::type_list_at_t<List, I>>>::type>::type;
    // clang-format on
    /// type list to  Tuple
    template<class List>
    struct type_list_to_tuple;

    template<class... Ts>
    struct type_list_to_tuple<type_traits::type_list<Ts...>> {
        using type = std::tuple<type_traits::decay_t<Ts>...>;
    };

    template<class... Ts>
    using type_list_to_tuple_t = typename type_list_to_tuple<Ts...>::type;

    // clang-format off
    template<class F, std::size_t... I>
    void apply_impl(F &&f, message *ctx, type_traits::index_sequence<I...>) {
        using call_trait =  type_traits::get_callable_trait_t<type_traits::remove_reference_t<F>>;
        constexpr int args_size = call_trait::number_of_arguments;
        using args_type_list = type_traits::tl_slice_t<typename call_trait::args_types, 0, args_size>;
        using Tuple =  type_list_to_tuple_t<args_type_list>;
        auto &args = ctx->body<Tuple>();
        ///f(static_cast< forward_arg<args_type_list, I>>(std::get<I>(args))...);
        f((std::get<I>(args))...);
    }

    // clang-format on
    template<typename F,
             class Args = typename type_traits::get_callable_trait<F>::args_types,
             int Args_size = type_traits::get_callable_trait<F>::number_of_arguments>
    struct transformer {
        auto operator()(F&& f) -> action {
            action tmp([func = std::move(f)](communication_module* ctx) -> void {
                apply_impl(func, ctx, type_traits::make_index_sequence<Args_size>{});
            });
            return tmp;
        }
    };

    template<typename F, class Args>
    struct transformer<F, Args, 0> final {
        auto operator()(F&& f) -> action {
            action tmp([func = std::move(f)](communication_module*) -> void {
                func();
            });
            return tmp;
        }
    };

    template<typename F, class Args>
    struct transformer<F, Args, 1> final {
        auto operator()(F&& f) -> action {
            action tmp([func = std::move(f)](message* ctx) -> void {
                using arg_type = type_traits::type_list_at_t<Args, 0>;
                using clear_args_type = type_traits::decay_t<arg_type>;
                auto& tmp = ctx->body<clear_args_type>();
                func(tmp);
            });
            return tmp;
        }
    };

    /// class method
    // clang-format off
    template<class F, typename ClassPtr, std::size_t... I>
    void apply_impl_for_class(F &&f, ClassPtr *ptr, message *ctx, type_traits::index_sequence<I...>) {
        using call_trait =  type_traits::get_callable_trait_t<type_traits::remove_reference_t<F>>;
        using args_type_list = typename call_trait::args_types;
        using Tuple =  type_list_to_tuple_t<args_type_list>;
        auto &args = ctx->body<Tuple>();
        //(ptr->*f)(static_cast< forward_arg<args_type_list, I>>(std::get<I>(args))...);
        (ptr->*f)((std::get<I>(args))...);
    }

    // clang-format on
    template<
        typename F,
        typename ClassPtr,
        class Args = typename type_traits::get_callable_trait<F>::args_types,
        int Args_size = type_traits::get_callable_trait<F>::number_of_arguments>
    struct transformer_for_class {
        auto operator()(F&& f, ClassPtr* ptr) -> action {
            action tmp([func = std::move(f), ptr](message* ctx) -> void {
                apply_impl_for_class(func, ptr, ctx, type_traits::make_index_sequence<Args_size>{});
            });
            return tmp;
        }
    };

    template<typename F, typename ClassPtr, class Args>
    struct transformer_for_class<F, ClassPtr, Args, 0> final {
        auto operator()(F&& f, ClassPtr* ptr) -> action {
            action tmp([func = std::move(f), ptr](message*) -> void {
                (ptr->*func)();
            });
            return tmp;
        }
    };

    template<typename F, typename ClassPtr, class Args>
    struct transformer_for_class<F, ClassPtr, Args, 1> final {
        auto operator()(F&& f, ClassPtr* ptr) -> action {
            action tmp([func = std::move(f), ptr](message* arg) -> void {
                using arg_type_0 = type_traits::type_list_at_t<Args, 0>;
                using decay_arg_type_0 = type_traits::decay_t<arg_type_0>;
                auto& tmp = arg->body<decay_arg_type_0>();
                using original_arg_type_0 = forward_arg<Args, 0>;
                (ptr->*func)(std::forward<original_arg_type_0>(static_cast<original_arg_type_0>(tmp)));
            });
            return tmp;
        }
    };

    template<typename F>
    auto make_handler(F&& f)-> action {
        return transformer<F>{}(std::forward<F>(f));
    }

    template<typename F, typename ClassPtr>
    auto make_handler(F&& f, ClassPtr* self) -> action {
        return transformer_for_class<F, ClassPtr>{}(std::forward<F>(f), self);
    }

}} // namespace actor_zeta::base
