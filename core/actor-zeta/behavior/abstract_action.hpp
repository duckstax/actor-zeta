#pragma once

#include <functional>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/behavior/type_action.hpp>

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

        class helper final : public abstract_action {
        public:
            ~helper() = default;

            template<
                    std::size_t N,
                    typename F
            >
            helper(const char(&aStr)[N],F f):
                    abstract_action(aStr),
                    helper_(f) {

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
