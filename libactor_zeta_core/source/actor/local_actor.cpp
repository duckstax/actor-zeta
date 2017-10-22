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
        local_actor::local_actor(environment::environment *env,mailbox_type* mail_ptr,behavior::abstract_behavior*behavior_ptr, const std::string &type)
                :mailbox_(mail_ptr),life(behavior_ptr), abstract_actor(env, type) {
            initialize();
        }

        void local_actor::initialize() {
            attach(new sync_contacts());
            attach(new skip());
            attach(new add_channel());
        }

        messaging::message local_actor::next_message() {
            return mailbox().get();
        }

        void local_actor::attach(behavior::abstract_action *ptr_aa) {
            life->insert(ptr_aa);
        }

        local_actor::~local_actor() {

        }

        bool local_actor::has_next_message() {
            messaging::message msg_ptr = mailbox().get();
            return push_to_cache(std::move(msg_ptr));
        }

        bool local_actor::push_to_cache(messaging::message &&msg_ptr) {
            return mailbox().push_to_cache(std::move(msg_ptr));
        }

        messaging::message local_actor::pop_to_cache() {
            return mailbox().pop_to_cache();
        }

        local_actor::mailbox_type &local_actor::mailbox() {
            return *mailbox_;
        }
    }
}