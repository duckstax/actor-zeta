#ifndef BOOKCONTACTS_HPP
#define BOOKCONTACTS_HPP

#include <string>
#include <vector>
#include <map>
#include "fwd.hpp"

namespace actor_model {

    class book_contacts {
    public:
        book_contacts() = default;

        book_contacts(std::initializer_list<actor_address> visiting_cards);

        book_contacts(std::vector<actor_address> visiting_cards);

        void put(std::initializer_list<actor_address> visiting_cards);

        void put(const std::vector<actor_address> &visiting_cards);

        actor_address &get(const std::string &name);

        void put(const std::string name, actor_address);

        void put(const actor_address &vc);

        std::vector<actor_address> to_vector();

        /*
        * debug method
        */
        void all_view();

    private:
        std::map<std::string, actor_address> contacts;
    };
}
#endif