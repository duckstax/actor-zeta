#pragma once

#include <actor-zeta/actor/base_actor.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace actor {

        class executable_actor : public base_actor  {
        public:
            virtual void launch(executor::execution_device*, bool /*hide*/) = 0;

            ~executable_actor() override ;
        protected:
            auto attach(executor::execution_device *) -> void;

            auto attach() const -> executor::execution_device* ;

            auto env() -> supervisor* ;

            executable_actor(supervisor *, detail::string_view);

        private:
            supervisor* supervisor_;
            executor::execution_device *executor_;

        };

}}