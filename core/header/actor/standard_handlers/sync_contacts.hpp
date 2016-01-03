#ifndef SYNC_CONTACTS_HPP
#define SYNC_CONTACTS_HPP

#include "messaging/message.hpp"
#include "actor/book_contacts.hpp"
#include "actor/actor_address.hpp"

namespace actor_zeta {

    struct sync_contacs {
        void operator()(book_contacts &bc, messaging::message &&msg) {
            bc.put(msg.get<actor_address>());
        }
    };
}


#endif //SYNC_CONTACTS_HPP
