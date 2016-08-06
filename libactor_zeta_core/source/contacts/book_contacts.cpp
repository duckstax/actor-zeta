#include <iostream>

#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/contacts/group_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {
    namespace contacts {

        const actor::actor_address& book_contacts::get(const std::string &name) {
            return contacts[name];
        }

        void book_contacts::put(const actor::actor_address &vc) {
            contacts.emplace(vc->type(), vc);
        }

        void book_contacts::all_view() {
            for (auto &i: contacts)
                std::cout << i.first << std::endl;

        }

        void book_contacts::put_in_group(const std::string &name, const actor::actor_address &address) {
            groups.at(name).put(address);
        }

        const actor::actor_address &book_contacts::get_group(const std::string &name ) {
            return groups[name].get();
        }
    }
}