#include <iostream>

#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/impl/handler.ipp>


namespace actor_zeta { namespace actor {

        abstract_actor::~abstract_actor() {

        }

        abstract_actor::abstract_actor(
                supervisor &env,
                detail::string_view name
        )
                : message_passing_interface(name,abstract::actor)
                , supervisor_(env){
        }

        executor::execution_device *abstract_actor::attach() const {
            return executor_;
        }

        void abstract_actor::attach(executor::execution_device *e) {
            if (e!= nullptr) {
                executor_ = e;
            }
        }

        auto abstract_actor::env() -> supervisor & {
            return supervisor_;
        }


}}
