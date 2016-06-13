#include <initializer_list>
#include "actor-zeta/actor/behavior.hpp"
#include "actor-zeta/actor/book_contacts.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "iostream"

namespace actor_zeta {

    void behavior::run(messaging::message &&d) {
        auto it = behavioral_reactions.find(d.type());
        it->second(std::move(d));
    }

    void behavior::all_name_view() {
        for (auto &i: behavioral_reactions) {
            std::cout << i.first << std::endl;
        }
    }

    void behavior::insert(const std::string &type, abstract_action *aa) {
        behavioral_reactions.emplace(type, std::move(action(aa)));
    }
}