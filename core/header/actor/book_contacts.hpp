#ifndef BOOKCONTACTS_HPP
#define BOOKCONTACTS_HPP

#include <string>
#include <vector>
#include <map>
#include "forwards.hpp"

namespace actor_zeta {

    class book_contacts {
    public:
        book_contacts() = default;

        book_contacts(std::initializer_list<actor_address> visiting_cards);

        book_contacts(std::vector<actor_address> visiting_cards);

        void put(std::initializer_list<actor_address> visiting_cards);

        void put(const std::vector<actor_address> &visiting_cards);

        void put(const std::string name, actor_address);

        void put(const actor_address &vc);

        actor_address &get(const std::string &name);

        /*
        * debug method
        */
        void all_view();

    private:
        class group{
        public:
            group();
            group(group&&)= default;
            group&operator=(group&&)= default;
            void put(const actor_address &vc);
            actor_address &get();
        private:
            int cursor;
            std::vector<actor_address>dd;
        };

        std::map<std::string, actor_address> contacts;
        std::map<std::string,group> groups;
    };
}
#endif