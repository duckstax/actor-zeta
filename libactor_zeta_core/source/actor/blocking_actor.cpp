#include "actor-zeta/actor/blocking_actor.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace actor {

        executor::executable::executable_result
        blocking_actor::run(executor::execution_device *e, size_t max_throughput) {
            if (e) {
                device(e);
            }

            auto self = this;
            self->act();
            return executor::executable::executable_result::done;
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
                messaging::message *msg_ptr = next_message();
                if (msg_ptr != nullptr) {
                    auto request = new behavior::request(contacts, msg_ptr);
                    auto response = life.run(request);
                    if (response != nullptr) {
                        response->receiver()->address()->async_send(response->message());
                    }
                    delete request;
                    if (response != nullptr) {
                        delete response;
                    }
                    delete msg_ptr;
                } else {
                    return;
                }
            }
        }

        blocking_actor::blocking_actor(environment::environment *env, const std::string &type)
                : local_actor(env, type) {}
    }
}
