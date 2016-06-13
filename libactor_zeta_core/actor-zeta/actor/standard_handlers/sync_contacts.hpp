#ifndef SYNC_CONTACTS_HPP
#define SYNC_CONTACTS_HPP

#include <actor-zeta/actor/behavior.hpp>
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/actor/book_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {

    class sync_contacts  final : public abstract_action {
    public:
        sync_contacts(book_contacts &bc) : bc(bc) {}

        void operator()(messaging::message &&msg) override {
            bc.put(msg.get<actor_address>());
        }

    private:
        book_contacts &bc;
    };
}


#endif //SYNC_CONTACTS_HPP
