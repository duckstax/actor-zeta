#include <initializer_list>
#include "actor/behavior.hpp"
#include "actor/book_contacts.hpp"
#include "messaging/message.hpp"

namespace actor_model {

    actor_model::behavior::behavior(
            std::initializer_list<std::pair<std::string, ::actor_model::behavior::action>> handlers)
            : behavioral_reactions(handlers.begin(), handlers.end()) { }

    void behavior::insert(std::string type, action &&f) {
        behavioral_reactions.emplace(type, f);
    }

/*
    void behavior::insert(std::initializer_list<std::pair<std::string, action>> lpsa) {
        for (auto &i:lpsa) {
            behavioral_reactions.emplace(i.first, i.second);
        }
    }
*/
    void behavior::run(book_contacts &contacts, messaging::message &&d) {
        auto it = behavioral_reactions.find(d.type());
        it->second(contacts, std::move(d));
    }

    void behavior::all_name_view() {
        for (auto &i: behavioral_reactions)
            std::cout << i.first << std::endl;
    }
}