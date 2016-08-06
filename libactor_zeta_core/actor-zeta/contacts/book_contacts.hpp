#ifndef BOOKCONTACTS_HPP
#define BOOKCONTACTS_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "actor-zeta/forwards.hpp"
#include "group_contacts.hpp"

namespace actor_zeta {
    namespace contacts {
        class book_contacts {
        public:
            book_contacts() = default;

            book_contacts(book_contacts &&) = default;

            book_contacts &operator=(book_contacts &&)= default;

            void put(const actor::actor_address &);

            const actor::actor_address& get(const std::string &);

            void put_in_group(const std::string&, const actor::actor_address &);

            const actor::actor_address& get_group(const std::string&);

            /*
            * debug method
            */
            void all_view();

        private:
            std::unordered_map<std::string, actor::actor_address> contacts;
            std::unordered_map<std::string, group_contacts> groups;
        };
    }
}
#endif