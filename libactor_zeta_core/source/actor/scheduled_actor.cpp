#include "actor-zeta/actor/scheduled_actor.hpp"
#include "actor-zeta/executor/abstract_coordinator.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/environment.hpp"
#include "actor-zeta/behavior/abstract_action.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace actor {

        executor::executable::executable_result
        scheduled_actor::run(executor::execution_device *e, size_t max_throughput) {
            if (e) {
                device(e); //TODO переписать обработка
            }

            //---------------------------------------------------------------------------

            {
                messaging::message *msg_ptr = nullptr;
                for (size_t handled_msgs = 0; handled_msgs < max_throughput;) {
                    msg_ptr = pop_to_cache();
                    if (msg_ptr != nullptr) {
                        auto request = new behavior::request(contacts, msg_ptr);
                        auto response = life.run(request);
                        if (response != nullptr) {
                            response->receiver()->address()->async_send(response->message());
                        }
                        ++handled_msgs;
                        delete request;
                        if (response != nullptr) {
                            delete response;
                        }
                        delete msg_ptr;
                        continue;
                    }
                    msg_ptr = next_message();
                    if (msg_ptr != nullptr) {
                        auto request = new behavior::request(contacts, msg_ptr);
                        auto response = life.run(request);
                        if (response != nullptr) {
                            response->receiver()->address()->async_send(response->message());
                        }
                        ++handled_msgs;
                        delete request;
                        if (response != nullptr) {
                            delete response;
                        }
                        delete msg_ptr;
                    } else {
                        return executable_result::awaiting;
                    }
                }
            }

            //---------------------------------------------------------------------------

            messaging::message *msg_ptr = next_message();
            while (msg_ptr != nullptr) {
                push_to_cache(msg_ptr);
                msg_ptr = next_message();
            }

            //---------------------------------------------------------------------------

            if (has_next_message()) {
                return executable_result::awaiting;
            }

            return executable_result::resume;
        }

        bool scheduled_actor::async_send(messaging::message *mep, executor::execution_device *e) {
            if (e) {
                device(e); //TODO переписать обработка
            }
            mailbox().put(mep);

            if (e) {
                device(e);
                device()->put_execute_latest(this);
            } else {
                env().manager_execution_device().submit(this);
            }
            return true;
        }


        void scheduled_actor::attach_to_scheduler() {
            ref();
        }

        void scheduled_actor::detach_from_scheduler() {
            deref();
        }

        scheduled_actor::scheduled_actor(environment::environment &env, const std::string &name)
                : local_actor(env, name) {
            local_actor::initialize();
        }

        void scheduled_actor::launch(executor::execution_device *e, bool hide) {
            if (e) {
                device(e);
            }

            if (hide) {//TODO:???
                device(e);
                device()->put_execute_latest(this);
            } else {
                auto max_throughput = std::numeric_limits<size_t>::max();
                while (run(device(), max_throughput) != executor::executable::executable_result::awaiting) {
                }
            }
        }

        bool scheduled_actor::async_send(messaging::message *msg) {
            return async_send(msg, nullptr);
        }
    }
}

