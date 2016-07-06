#include "actor-zeta/contacts/group_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace contacts {
        const actor_zeta::actor::actor_address &group_contacts::get() {
            const actor_zeta::actor::actor_address & element = set_contact.at(cursor);
            ++cursor;
            if (cursor >= set_contact.size()) {
                cursor = 0;
            }
            return element;
        }

        void group_contacts::put(const actor_zeta::actor::actor_address &vc) {
            set_contact.push_back(vc);
        }

        group_contacts::group_contacts() : cursor(0) {}

        const std::vector<actor_zeta::actor::actor_address> &group_contacts::get_all() const {
            return set_contact;
        }
    }
}
