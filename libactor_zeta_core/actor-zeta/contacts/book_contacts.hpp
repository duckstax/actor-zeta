#ifndef BOOKCONTACTS_HPP
#define BOOKCONTACTS_HPP

#include <string>
#include <vector>
#include <map>
#include "actor-zeta/forwards.hpp"
#include "group_contacts.hpp"

namespace actor_zeta {
    namespace contacts {
        class book_contacts {
        public:
            book_contacts() = default;

            void put(std::initializer_list<actor::actor_address> visiting_cards);

            void put(const std::vector<actor::actor_address> &visiting_cards);

            void put(const actor::actor_address &vc);

            actor::actor_address &get(const std::string &name);

            /*
            * debug method
            */
            void all_view();

        private:
            std::map<std::string, actor::actor_address> contacts;
            std::map<std::string, group_contacts> groups;
        };
    }
}
#endif