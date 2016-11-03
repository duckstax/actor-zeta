#include "actor-zeta/standard_handlers/sync_contacts.hpp"

namespace actor_zeta {

    sync_contacts::sync_contacts(contacts::book_contacts &bc) : bc(bc), abstract_action("sync_contacts") {}

    void sync_contacts::operator()(messaging::message *msg) {
        bc.put(msg->get<actor::actor_address>());
    }
}