#pragma once

#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/type_list.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
// clang-format off
template <class List, std::size_t I>
using forward_arg =
  typename std::conditional<std::is_lvalue_reference<type_traits::type_list_at_t<List, I>>::value,
  typename std::add_lvalue_reference<type_traits::decay_t<type_traits::type_list_at_t<List, I>>>::type,
  typename std::add_rvalue_reference<type_traits::decay_t<type_traits::type_list_at_t<List, I>>>::type>::type;
// clang-format on
/// type list to  Tuple
template <class List>
struct type_list_to_tuple;

template <class... Ts>
struct type_list_to_tuple<type_traits::type_list<Ts...>> {
  using type = std::tuple<type_traits::decay_t<Ts>...>;
};

template <class... Ts>
using type_list_to_tuple_t = typename type_list_to_tuple<Ts...>::type;

// clang-format off
template<class Context, class F, std::size_t... I>
void apply_impl(Context &ctx,F &&f,  type_traits::index_sequence<I...>) {
    using call_trait =  type_traits::get_callable_trait_t<type_traits::remove_reference_t<F>>;
    constexpr int args_size = call_trait::number_of_arguments;
    using args_type_list = type_traits::tl_slice_t<typename call_trait::args_types, 1, args_size>;
    using Tuple =  type_list_to_tuple_t<args_type_list>;
    auto &args = ctx.current_message().template body<Tuple>();
    using type_context = type_traits::type_list_at_t<typename call_trait::args_types, 0>;
    using clear_type_context = type_traits::decay_t<type_context>;
    f(static_cast<typename std::add_lvalue_reference<clear_type_context>::type >(ctx), static_cast< forward_arg<args_type_list, I>>(std::get<I>(args))...);
}
// clang-format on

template <
    typename Context,
    typename F,
    class Args = typename type_traits::get_callable_trait<F>::args_types,
    int Args_size = type_traits::get_callable_trait<F>::number_of_arguments
    >
struct transformer {
  auto operator()(Context&& ctx, F&& f) -> std::function<void()> {
    return [ctx,f]() -> void {
      using call_trait =
        type_traits::get_callable_trait_t<type_traits::remove_reference_t<F>>;
      constexpr int args_size = call_trait::number_of_arguments;
      apply_impl(f, ctx, type_traits::make_index_sequence<args_size - 1>{});
    };
  }
};

template <typename Context,typename F, class Args>
struct transformer<Context,F, Args, 0> final {
  auto operator()(Context&&ctx,F&& f) -> std::function<void()> {
    return [f]() -> void { f(); };
  }
};

template <typename Context,typename F, class Args>
struct transformer<Context,F, Args, 1> final {
  auto operator()(Context&&ctx,F&& f) -> std::function<void()> {
    return [ctx,f]() -> void {
      using type_context = type_traits::type_list_at_t<Args, 0>;
      using clear_type_context = type_traits::decay_t<type_context>;
      return f(
        static_cast<
          typename std::add_lvalue_reference<clear_type_context>::type>(ctx));
    };
  }
};

template <typename Context,typename F, class Args>
struct transformer<Context,F, Args, 2> final {
  auto operator()(Context&&ctx,F&& f) -> std::function<void()> {
    return [ctx,f]() -> void {
      using type_context = type_traits::type_list_at_t<Args, 0>;
      using clear_type_context = type_traits::decay_t<type_context>;
      using arg_type_2 = type_traits::type_list_at_t<Args, 1>;
      using clear_args_type_2 = type_traits::decay_t<arg_type_2>;
      auto& tmp = ctx.current_message().template body<clear_args_type_2>();
      f(static_cast<
          typename std::add_lvalue_reference<clear_type_context>::type>(ctx),
        tmp);
    };
  }
};

/// class method
// clang-format off
template<typename Context,class F, typename ClassPtr, std::size_t... I>
void apply_impl_for_class(F &&f, ClassPtr *ptr, Context &ctx, type_traits::index_sequence<I...>) {
    using call_trait =  type_traits::get_callable_trait_t<type_traits::remove_reference_t<F>>;
    using args_type_list = typename call_trait::args_types;
    using Tuple =  type_list_to_tuple_t<args_type_list>;
    auto &args = ctx.current_message().template body<Tuple>();
    (ptr->*f)(static_cast< forward_arg<args_type_list, I>>(std::get<I>(args))...);
}
// clang-format on
template <
    typename Context,
    typename F,
    typename ClassPtr,
    class Args = typename type_traits::get_callable_trait<F>::args_types,
    int Args_size = type_traits::get_callable_trait<F>::number_of_arguments
>
struct transformer_for_class {
  auto operator()(Context& ctx,F&& f, ClassPtr* ptr) -> std::function<void()> {
    return [ctx,f, ptr]() -> void {
      using call_trait = type_traits::get_callable_trait_t<type_traits::remove_reference_t<F>>;
      constexpr int args_size = call_trait::number_of_arguments;
      apply_impl_for_class(f, ptr, ctx,type_traits::make_index_sequence<args_size>{});
    };
  }
};

template <typename Context,typename F, typename ClassPtr, class Args>
struct transformer_for_class<Context,F, ClassPtr, Args, 0> final {
  auto operator()(Context& ctx,F&& f, ClassPtr* ptr) -> std::function<void()> {
    return [ctx,f, ptr]() -> void { (ptr->*f)(); };
  }
};

template <typename Context,typename F, typename ClassPtr, class Args>
struct transformer_for_class<Context,F, ClassPtr, Args, 1> final {
  auto operator()(Context&&ctx,F&& f, ClassPtr* ptr) -> std::function<void()> {
    return [ctx,f, ptr]() mutable -> void {
      using arg_type_0 = type_traits::type_list_at_t<Args, 0>;
      using decay_arg_type_0 = type_traits::decay_t<arg_type_0>;
      auto& tmp = ctx.current_message().template body<decay_arg_type_0>();
      using original_arg_type_0 = forward_arg<Args, 0>;
      (ptr->*f)(std::forward<original_arg_type_0>(static_cast<original_arg_type_0>(tmp)));
    };
  }
};

template <typename Context,typename F>
auto make_handler_base(Context&&ctx,F&& f) -> handler* {
  return  transformer<Context,F>{}(std::forward<Context>(ctx),std::forward<F>(f));
}

template <typename Context,typename F, typename ClassPtr>
auto make_handler_base(Context&&ctx,F&& f, ClassPtr* self) -> handler* {
  return transformer_for_class<Context,F, ClassPtr>{}(std::forward<Context>(ctx),std::forward<F>(f), self);
}

}}