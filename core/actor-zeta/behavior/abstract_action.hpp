#pragma once

#include <functional>

#include <actor-zeta/behavior/context.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/behavior/type_action.hpp>
#include <actor-zeta/detail/type_traits/callable_trait.hpp>

namespace actor_zeta { namespace behavior {
///
/// @brief Abstract concept of an action
///
        class abstract_action {      
        public:
            virtual ~abstract_action();

            template<std::size_t N>
            abstract_action(const char(&aStr)[N]) : name_(aStr) {}

            virtual void invoke(context &) = 0;

            auto name() const -> const type_action &;

        private:
            const type_action name_;
        };

        template <
                typename F,
                class Args = typename type_traits::get_callable_trait<F>::arg_types,
                int Args_size = type_traits::type_list_size<typename type_traits::get_callable_trait<F>::arg_types>::value
        >
        struct transformer;

        template <
                typename F,
                class Args
        >
        struct transformer<F,Args,1>  {
            auto operator()(F&&f)-> std::function<void(context&)> {
                return f;
            }
        };

        template <
                typename F,
                class Args
        >
        struct transformer<F,Args,2> {
            auto operator()(F&&f)-> std::function<void(context&)> {
                return [f](context &arg) -> void {
                    using arg_type_2 = typename type_traits::type_list_at<Args, 1>::type;
                    using clear_args_type_2 = typename std::decay<arg_type_2>::type;
                    auto& tmp = arg.message().body<clear_args_type_2>();
                    f(arg, tmp);
                };
            }
        };


        class helper final : public abstract_action {
        public:
            ~helper() = default;

            template<
                    std::size_t N,
                    typename F
            >
            helper(const char(&aStr)[N],F&&f):
                    abstract_action(aStr){
                    helper_= transformer<F>{}(std::forward<F>(f));
            }

            void invoke(context& ctx) {
                helper_(ctx);
            }
        private:
            std::function<void(context&)> helper_;

        };

        template<std::size_t N,typename F>
        auto make_handler(const char(&aStr)[N],F&&f) -> abstract_action* {
            return new helper(aStr,f);
        };

    } /// namespace behavior
} /// namespace actor_zeta
