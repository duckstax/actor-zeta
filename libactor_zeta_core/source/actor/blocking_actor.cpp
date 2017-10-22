#include "actor-zeta/actor/blocking_actor.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace actor {

        executor::executable_result
        blocking_actor::run(executor::execution_device *e, size_t max_throughput) {
            device(e);
            auto self = this;
            for (;;) {
                messaging::message msg_ptr = next_message();
                if (msg_ptr) {
                    behavior::request request(contacts, std::move(msg_ptr));
                    auto response = life->run(std::move(request));
                    if (response) {
                        response.receiver()->address()->send(std::move(response.message()));
                    }
                } else {
                    return executor::executable_result::done;
                }
            }
            return executor::executable_result::done;
        }

        void blocking_actor::launch(executor::execution_device *e, bool hide) {
            device(e);
            if (hide) {//TODO:???
                device(e);
                device()->put_execute_latest(this);
            } else {
                auto self = this;
                this->run(e,std::numeric_limits<std::size_t>::max());
            }
        }

        blocking_actor::blocking_actor(environment::environment *env,mailbox_type* mail,behavior::abstract_behavior* behavior_ptr, const std::string &type)
                : local_actor(env,mail,behavior_ptr, type) {}
    }
}
