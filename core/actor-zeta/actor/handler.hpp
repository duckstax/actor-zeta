#pragma once

#include <functional>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/callable_trait.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Abstract concept of an action
///
        class handler {
        public:
            virtual ~handler() = default;

            virtual void invoke(context &) = 0;
        };

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
                    auto &tmp = arg.message().body<clear_args_type_2>();
                    f(arg, tmp);
                };
            }
        };


        class helper final : public handler {
        public:
            ~helper() override = default;

            template<typename F>
            helper( F &&f){
                helper_ = transformer<F>{}(std::forward<F>(f));
            }

            void invoke(context &ctx) final {
                helper_(ctx);
            }

        private:
            std::function<void(context & )> helper_;

        };

        template< typename F>
        auto make_handler( F &&f) -> handler * {
            return new helper(f);
        };

}} /// namespace actor_zeta { namespace behavior {}}
