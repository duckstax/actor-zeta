#ifndef SYNC_CONTACTS_HPP
#define SYNC_CONTACTS_HPP

#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/actor/book_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {

    struct sync_contacts {
        void operator()(book_contacts &bc, messaging::message &&msg) {
            bc.put(msg.get<actor_address>());
        }
    };
}


#endif //SYNC_CONTACTS_HPP
