#pragma once

#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/actor/context.hpp>

namespace actor_zeta { namespace actor {

        class executable_actor
                : public abstract_actor
                , public context {
        public:
            ///TODO:
            ///virtual void launch(executor::execution_device*, bool /*hide*/) = 0;

            ~executable_actor() override ;
        protected:
            auto attach(executor::execution_device *) -> void;

            auto attach() const -> executor::execution_device* ;

            auto env() -> supervisor& ;

            executable_actor(supervisor &, detail::string_view);

        private:
            supervisor& supervisor_;
            executor::execution_device *executor_;

        };

}}