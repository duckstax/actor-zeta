#include <initializer_list>
#include "iostream"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/behavior/action.hpp"

namespace actor_zeta {
    namespace behavior {
        void behavior::run(messaging::message &&d) {
            auto it = behavioral_reactions.find(d.type());
            if(it!=behavioral_reactions.end()) {
                it->second(std::move(d));
            }
        }

        void behavior::all_name_view() {
            for (auto &i: behavioral_reactions) {
                std::cout << i.first << std::endl;
            }
        }

        void behavior::insert(interface_action *aa) {
            behavioral_reactions.emplace(aa->name(), std::move(action(aa)));
        }
    }
}