#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/type_list.hpp>


namespace actor_zeta { namespace actor {
        template<
                typename F,
                class Args = typename type_traits::get_callable_trait<F>::arg_types,
                int Args_size = type_traits::type_list_size<typename type_traits::get_callable_trait<F>::arg_types>::value
        >
        struct transformer;

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


        template <class F, class Tuple, std::size_t... I>
        void apply_impl(F&& f,context& ctx, Tuple&& t, type_traits::index_sequence<I...>){
            f(ctx,std::get<I>(std::forward<Tuple>(t))...);
        }

        template<
                typename F,
                class Args
        >
        struct transformer<F, Args, 3>  {
            auto operator()(F &&f) -> std::function<void(context & )> {
                return [f](context &ctx) -> void {
                    using CallTraits =  type_traits::get_callable_trait<type_traits::remove_reference_t<F>>;
                    using arg_type = typename CallTraits::arg_types;
                    using Tuple = std::tuple<type_traits::decay_t<arg_type>>;
                    auto &args_ = *detail::any_cast<Tuple>(&ctx.current_message().body());
                    constexpr int Args_size = type_traits::type_list_size<typename type_traits::get_callable_trait<F>::arg_types>::value;
                    apply_impl(std::forward<F>(f), ctx, std::move(args_),type_traits::make_index_sequence<Args_size>{});
                };
            }
        };


    template<typename F>
    helper::helper(F &&f) {
        helper_ = transformer<F>{}(std::forward<F>(f));
    }

}}