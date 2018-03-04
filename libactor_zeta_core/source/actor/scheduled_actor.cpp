#include <iostream>
#include "actor-zeta/actor/scheduled_actor.hpp"
#include "actor-zeta/executor/abstract_coordinator.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/environment/environment.hpp"
#include "actor-zeta/behavior/abstract_action.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace actor {

        void error(){
            std::cerr << " WARNING " << std::endl;
            std::cerr << " WRONG ADDRESS " << std::endl;
            std::cerr << " WARNING " << std::endl;
        }

        executor::executable_result scheduled_actor::run(executor::execution_device *e, size_t max_throughput) {
            device(e);
            //---------------------------------------------------------------------------

            {
                messaging::message msg_ptr;
                for (size_t handled_msgs = 0; handled_msgs < max_throughput;) {
                    msg_ptr = pop_to_cache();
                    if (msg_ptr) {
                        behavior::request request(contacts, std::move(msg_ptr));
                        auto response = life->run(std::move(request));
                        if (response ) {
                            if (response.receiver()->address()) {
                                response.receiver()->address()->send(std::move(response.message()));
                            } else {
                                error();
                            }
                        }
                        ++handled_msgs;
                        continue;
                    }

                    msg_ptr = next_message();
                    if (msg_ptr) {
                        auto request = behavior::request(contacts, std::move(msg_ptr));
                        auto response = life->run(std::move(request));
                        if (response ) {
                            if (response.receiver()->address()) {
                                response.receiver()->address()->send(std::move(response.message()));
                            } else {
                                error();
                            }
                        }
                        ++handled_msgs;

                    } else {
                        return executor::executable_result::awaiting;
                    }
                }
            }

            //---------------------------------------------------------------------------

            messaging::message msg_ptr = next_message();
            while (msg_ptr) {
                push_to_cache(std::move(msg_ptr));
                msg_ptr = next_message();
            }

            //---------------------------------------------------------------------------

            if (has_next_message()) {
                return executor::executable_result::awaiting;
            }

            return executor::executable_result::resume;
        }

        bool scheduled_actor::send(messaging::message && mep, executor::execution_device *e) {
            device(e);
            mailbox().put(std::move(mep));

            if (e != nullptr) {
                device(e);
                device()->put_execute_latest(this);
            } else {
                env()->manager_execution_device().submit(this);
            }
            return true;
        }


        void scheduled_actor::attach_to_scheduler() {
            ref();
        }

        void scheduled_actor::detach_from_scheduler() {
            deref();
        }

        scheduled_actor::scheduled_actor(environment::abstract_environment *env,mailbox_type* mail_ptr,behavior::abstract_behavior*behavior_ptr, const std::string &name)
                : local_actor(env,mail_ptr,behavior_ptr, name) {
            local_actor::initialize();
        }

        void scheduled_actor::launch(executor::execution_device *e, bool hide) {
            device(e);

            if (hide) {//TODO:???
                device()->put_execute_latest(this);
            } else {
                auto max_throughput = std::numeric_limits<size_t>::max();
                while (run(device(), max_throughput) != executor::executable_result::awaiting) {
                }
            }
        }

        bool scheduled_actor::send(messaging::message&&msg) {
            return send(std::move(msg), nullptr);
        }

        scheduled_actor::~scheduled_actor(){

        }
    }
}

