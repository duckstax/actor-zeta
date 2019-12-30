#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/type_list.hpp>
#include <type_traits>


namespace actor_zeta { namespace actor {
        template<
                typename F,
                class Args = typename type_traits::get_callable_trait<F>::args_types,
                int Args_size = type_traits::get_callable_trait<F>::number_of_arguments
        >
        struct transformer;

        template<
                typename F,
                class Args
        >
        struct transformer<F, Args, 0> {
            auto operator()(F &&f) -> std::function<void(context & )> {
                return [f](context &) -> void {
                    f();
                };
            }
        };


        template<
                typename F,
                class Args
        >
        struct transformer<F, Args, 1> {
            auto operator()(F &&f) -> std::function<void(context & )> {
                return f;
            }
        };

        template<
                typename F,
                class Args
        >
        struct transformer<F, Args, 2> {
            auto operator()(F &&f) -> std::function<void(context & )> {
                return [f](context &arg) -> void {
                    using arg_type_2 = typename type_traits::type_list_at<Args, 1>::type;
                    using clear_args_type_2 = typename std::decay<arg_type_2>::type;
                    auto &tmp = arg.current_message().body<clear_args_type_2>();
                    f(arg, tmp);
                };
            }
        };

        template <class List , std::size_t  I>
        using  forward_arg =
                typename std::conditional<std::is_lvalue_reference<type_traits::type_list_at_t<List, I>>::value,
                typename std::add_lvalue_reference<type_traits::decay_t<type_traits::type_list_at_t<List, I>> >::type,
                typename std::add_rvalue_reference<type_traits::decay_t<type_traits::type_list_at_t<List, I>>>::type
        >::type;

        template <class F, class Tuple, std::size_t... I>
        void apply_impl(F&& f,context& ctx, Tuple&& t, type_traits::index_sequence<I...>){
            using call_trait =  type_traits::get_callable_trait<type_traits::remove_reference_t<F>>;
            constexpr int args_size = call_trait::number_of_arguments;
            using args_type_list = typename type_traits::tl_slice_t<typename call_trait::args_types,1,args_size>;
            f(ctx,static_cast< forward_arg<args_type_list,I>>(std::get<I>(t))...);
        }

        /// type list to  Tuple
        template<class List>
        struct type_list_to_tuple;

        template<class... Ts>
        struct type_list_to_tuple<type_traits::type_list<Ts...>> {
            using type = std::tuple<type_traits::decay_t<Ts>...>;
        };

        template<
                typename F,
                class Args
        >
        struct transformer<F, Args, 3>  {
            auto operator()(F &&f) -> std::function<void(context & )> {
                return [f](context &ctx) -> void {
                    using call_trait =  type_traits::get_callable_trait<type_traits::remove_reference_t<F>>;
                    constexpr int args_size = call_trait::number_of_arguments;
                    using args_type_list =  typename type_traits::tl_slice_t<typename call_trait::args_types,1,args_size>;
                    using Tuple =  typename type_list_to_tuple<args_type_list>::type;
                    auto &args = ctx.current_message().body<Tuple>();
                    apply_impl(f, ctx, std::move(args),type_traits::make_index_sequence<args_size-1>{});
                };
            }
        };

        template<
                typename F,
                class Args
        >
        struct transformer<F, Args, 4>  {
            auto operator()(F &&f) -> std::function<void(context & )> {
                return [f](context &ctx) -> void {
                    using call_trait =  type_traits::get_callable_trait<type_traits::remove_reference_t<F>>;
                    constexpr int args_size = call_trait::number_of_arguments;
                    using args_type_list =  typename type_traits::tl_slice_t<typename call_trait::args_types,1,args_size>;
                    using Tuple =  typename type_list_to_tuple<args_type_list>::type;
                    auto &args = ctx.current_message().body<Tuple>();
                    apply_impl(f, ctx, std::move(args),type_traits::make_index_sequence<args_size-1>{});
                };
            }
        };


    template<typename F>
    helper::helper(F &&f) {
        helper_ = transformer<F>{}(std::forward<F>(f));
    }

}}