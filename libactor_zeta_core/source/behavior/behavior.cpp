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
            return behavioral_reactions.at("skip")(d);
        }

        void behavior::insert(abstract_action *aa) {
            behavioral_reactions.emplace(aa->name(),std::move(action(aa)));
        }
    }
}