#include <utility>
#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/standard_handlers/skip.hpp"
#include "actor-zeta/standard_handlers/sync_contacts.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/environment.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/messaging/message_priority.hpp"
#include "actor-zeta/standard_handlers/add_channel.hpp"

namespace actor_zeta {

    namespace actor {
        local_actor::local_actor(environment::environment *env, const std::string &type)
                : abstract_actor(env, type) {
            initialize();
        }

        void local_actor::initialize() {
            attach(new sync_contacts());
            attach(new skip());
            attach(new add_channel());
        }

        messaging::message *local_actor::next_message() {
            return mailbox().get();
        }

        void local_actor::attach(behavior::abstract_action *ptr_aa) {
            life.insert(ptr_aa);
        }

        local_actor::~local_actor() {

        }

        bool local_actor::has_next_message() {
            messaging::message *msg_ptr = mailbox().get();
            return push_to_cache(msg_ptr);
        }

        bool local_actor::push_to_cache(messaging::message *msg_ptr) {
            if (msg_ptr != nullptr) {
                switch (msg_ptr->priority()) {

                    case messaging::message_priority::low: {
                        mailbox().low_priority_cache().push_back(msg_ptr);
                        return true;
                    }

                    case messaging::message_priority::normal: {
                        mailbox().normal_priority_cache().push_back(msg_ptr);
                        return true;
                    }

                    case messaging::message_priority::high: {
                        mailbox().high_priority_cache().push_back(msg_ptr);
                        return true;
                    }
                }
            } else {
                return false;
            }
        }

        messaging::message *local_actor::pop_to_cache() {
            messaging::message *msg_ptr = nullptr;
            if (!mailbox().high_priority_cache().empty()) {
                msg_ptr = mailbox().high_priority_cache().front();
                mailbox().high_priority_cache().pop_front();
                return msg_ptr;
            }

            if (!mailbox().normal_priority_cache().empty()) {
                msg_ptr = mailbox().normal_priority_cache().front();
                mailbox().normal_priority_cache().pop_front();
                return msg_ptr;
            }

            if (!mailbox().low_priority_cache().empty()) {
                msg_ptr = mailbox().low_priority_cache().front();
                mailbox().low_priority_cache().pop_front();
                return msg_ptr;
            }
            return msg_ptr;
        }
    }
}