#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/executable_actor.hpp>

namespace actor_zeta { namespace actor {

        executable_actor::executable_actor(
                supervisor &env,
                detail::string_view name
        )
                : abstract_actor(name)
                , supervisor_(env){
        }

        executable_actor::~executable_actor() {

        }

        executor::execution_device *executable_actor::attach() const {
            return executor_;
        }

        void executable_actor::attach(executor::execution_device *e) {
            if (e!= nullptr) {
                executor_ = e;
            }
        }

        auto executable_actor::env() -> supervisor & {
            return supervisor_;
        }
        
}}