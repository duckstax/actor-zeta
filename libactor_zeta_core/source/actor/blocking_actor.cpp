#include "actor-zeta/actor/blocking_actor.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/messaging/message.hpp"


namespace actor_zeta {
    namespace actor {

        executor::executable::executable_result
        blocking_actor::run(executor::execution_device *e, size_t max_throughput) {
            if (e) {
                device(e);
            }

            if (blocked()) {
                auto self = this;
                self->act();
                return executor::executable::executable_result::done;
            }

            return executor::executable::executable_result::awaiting;
        }

        void blocking_actor::launch(executor::execution_device *e, bool hide) {
            if (e) {
                device(e);
            }

            if (hide) {//TODO:???
                device(e);
                device()->put_execute_latest(this);
            } else {
                auto self = this;
                self->act();
            }
        }

        void blocking_actor::act() {
            for (;;) {
                if (mailbox().empty()) {
                    auto msg = next_message();
                    life.run(msg);
                }
                else {
                    break;
                }
            }
        }

        blocking_actor::blocking_actor(environment::environment &env, const std::string &type)
                : local_actor(env,type) {
            blocked(true);
        }
    }
}
