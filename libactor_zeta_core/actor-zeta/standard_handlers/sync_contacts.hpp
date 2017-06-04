#ifndef SYNC_CONTACTS_HPP
#define SYNC_CONTACTS_HPP

#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
///
/// @brief
///
    class sync_contacts final : public behavior::abstract_action {
    public:
        sync_contacts();

        behavior::response *operator()(behavior::request *) override final;

    };
}

#endif //SYNC_CONTACTS_HPP
