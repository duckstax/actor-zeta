#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/actor/message_passing_interface.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Abstract concept of an actor
///

        class abstract_actor : public message_passing_interface  {
        public:
            abstract_actor()= delete;

            abstract_actor(const abstract_actor &) = delete;

            abstract_actor &operator=(const abstract_actor &) = delete;

            ~abstract_actor() override;

            ///TODO:
            ///virtual void launch(executor::execution_device*, bool /*hide*/) = 0;

            abstract_actor(supervisor &,detail::string_view);
        protected:
            auto attach(executor::execution_device *) -> void;

            auto attach() const -> executor::execution_device* ;

            auto env() -> supervisor& ;

        private:
            supervisor& supervisor_;
            executor::execution_device *executor_;
        };

}}
