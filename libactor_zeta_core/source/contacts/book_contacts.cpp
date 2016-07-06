#include <iostream>

#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/contacts/group_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace contacts {
        void book_contacts::put(std::initializer_list<actor::actor_address> visiting_cards) {
            for (auto &i: visiting_cards)
                contacts.emplace(i->type(), i);
        }

        actor::actor_address &book_contacts::get(const std::string &name) {
            return contacts[name];
        }

        void book_contacts::put(const actor::actor_address &vc) {
            contacts.emplace(vc->type(), vc);
        }

        void book_contacts::all_view() {
            for (auto &i: contacts)
                std::cout << i.first << std::endl;

        }

        void book_contacts::put(const std::vector<actor::actor_address> &visiting_cards) {
            for (auto &i: visiting_cards) {
                contacts.emplace(i->type(), i);
            }
        }
    }
}