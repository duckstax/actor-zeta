#include "actor/book_contacts.hpp"
#include "actor/actor_address.hpp"
#include <iostream>

namespace actor_model {

    book_contacts::book_contacts(std::initializer_list<actor_address> visiting_cards) {
        for (auto &i: visiting_cards)
            contacts.emplace();
    }

    book_contacts::book_contacts(std::vector<actor_address> visiting_cards) {
        for (auto &i: visiting_cards)
            contacts.emplace(i->type(), i);
    }

    void book_contacts::put(std::initializer_list<actor_address> visiting_cards) {
        for (auto &i: visiting_cards)
            contacts.emplace(i->type(), i);
    }

    actor_address &book_contacts::get(const std::string &name) {
        return contacts[name];
    }

    void book_contacts::put(const std::string name, actor_address a) {
        contacts.emplace(name, a);
    }

    void book_contacts::put(const actor_address &vc) {
        contacts.emplace(vc->type(), vc);
    }

    std::vector<actor_address> book_contacts::to_vector() {
        std::vector<actor_address> tmp;
        for (auto &i:contacts)
            tmp.emplace_back(actor_address(i.second));
        return tmp;
    }

    void book_contacts::all_view() {
        for (auto &i: contacts)
            std::cout << i.first << std::endl;

    }

    void book_contacts::put(const std::vector<actor_address> &visiting_cards) {
        for (auto &i: visiting_cards)
            contacts.emplace(i->type(), i);

    }
}