#include <initializer_list>
#include "iostream"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace behavior {
        response *behavior::run(request *d) {
            auto it = behavioral_reactions.find(d->message()->type());
            if (it != behavioral_reactions.end()) {
                return it->second(d);
            }
            return nullptr;//TODO : SKIP !!!
        }

        void behavior::all_name_view() {
            for (auto &i: behavioral_reactions) {
                std::cout << i.first << std::endl;
            }
        }

        void behavior::insert(abstract_action *aa) {
            behavioral_reactions.emplace(aa->name(), aa);
        }
    }
}