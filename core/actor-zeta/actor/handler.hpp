#pragma once

#include <functional>

#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Abstract concept of an action
///
        class handler {
        public:
            virtual ~handler() = default;

            virtual void invoke(context &) = 0;
        };

        class helper final : public handler   {
        public:
            ~helper() override = default;

            template<typename F>
            helper( F &&f);

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
