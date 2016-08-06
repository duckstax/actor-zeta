#include <utility>
#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/standard_handlers/skip.hpp"
#include "actor-zeta/standard_handlers/sync_contacts.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/executor/abstract_coordinator.hpp"
#include "actor-zeta/environment.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {

    namespace actor {
        local_actor::local_actor(environment::environment &env, const std::string &type)
                : abstract_actor(env, type) {
            initialize();
        }

        void local_actor::initialize() {
            life.insert(new actor_zeta::sync_contacts(contacts));
            life.insert(new actor_zeta::skip());
        }

        bool local_actor::async_send(messaging::message &&document) {
            return async_send(std::move(document), nullptr);
        }

        bool local_actor::async_send(messaging::message &&document, executor::execution_device *e) {
            if (e) {
                device(e);
            }
            bool status = mailbox.put(std::move(document));
            // schedule actor
            shedule(e);
            return status;
        }

        void local_actor::attach_to_scheduler() {
            ref();
        }

        void local_actor::detach_from_scheduler() {
            deref();
        }

        executor::executable::executable_result local_actor::run(executor::execution_device *e, size_t max_throughput) {
            if (e) {
                device(e);
            }

            for (int i = 0; i < max_throughput; ++i) {
                if (mailbox.empty()) {
                    auto msg = std::move(next_message());
                    life.run(std::move(msg));
                } else {
                    return executor::executable::executable_result::awaiting;
                }
            }

            return executor::executable::executable_result::done;
        };

        void local_actor::launch(executor::execution_device *e, bool hide) {
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
        };

        void local_actor::shedule(executor::execution_device *e) {
            // schedule actor
            if (e) {
                device(e);
                device()->put_execute_latest(this);
            }
            else {
                env.manager_execution_device().submit(this);
            }
        }

        messaging::message local_actor::next_message() {
            return mailbox.get();
        }

        void local_actor::attach(actor_zeta::behavior::interface_action *ptr_aa) {
            life.insert(ptr_aa);
        }

        bool local_actor::finalize() {
            return true;
        }

        local_actor::~local_actor()  {
            finalize();
        }
    }
}