#include <utility>
#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/standard_handlers/skip.hpp"
#include "actor-zeta/standard_handlers/sync_contacts.hpp"
#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/environment.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/messaging/message_priorities.hpp"

namespace actor_zeta {

    namespace actor {
        local_actor::local_actor(environment::environment &env, const std::string &type)
                : abstract_actor(env, type) {
            initialize();
        }

        void local_actor::initialize() {
            attach(new actor_zeta::sync_contacts(contacts));
            attach(new actor_zeta::skip());
        }

        messaging::message* local_actor::next_message() {
            return mailbox().get();
        }

        void local_actor::attach(actor_zeta::behavior::interface_action *ptr_aa) {
            life.insert(ptr_aa);
        }

        local_actor::~local_actor() {

        }

        bool local_actor::has_next_message() {
            return mailbox().empty();
        }

        //void local_actor::push_to_cache(messaging::message *element) {
            //TODO реализовать
        //}
    }
}