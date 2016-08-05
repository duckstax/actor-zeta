#ifndef SYNC_CONTACTS_HPP
#define SYNC_CONTACTS_HPP

#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {

    class sync_contacts  final : public behavior::interface_action {
    public:
        sync_contacts(contacts::book_contacts &bc) : bc(bc),name_("sync_contacts") {}

        void operator()(messaging::message &&msg) override final {
            bc.put(msg.get<actor::actor_address>());
        }

        const std::string& name() const override final {
            return name_;
        };

    private:
        contacts::book_contacts &bc;
        std::string name_;
    };
}


#endif //SYNC_CONTACTS_HPP
