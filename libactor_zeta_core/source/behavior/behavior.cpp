#include <initializer_list>
#include "iostream"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace behavior {

        void error(const std::string &_error_) {
            std::cerr << "Duplicate" << std::endl;
            std::cerr << "Handler: " << _error_ << std::endl;
            std::cerr << "Duplicate" << std::endl;
        }

        response behavior::run(request &&d) {
            auto it = behavioral_reactions.find(d.message().type());
            if (it != behavioral_reactions.end()) {
                return it->second(std::move(d));
            }
            return behavioral_reactions.at("skip")(std::move(d));
        }

        bool behavior::insert(abstract_action *aa) {
            auto it = behavioral_reactions.emplace(aa->name(), std::move(action(aa)));
            bool add = it.second;
            if (!add) {
                error(aa->name().to_string());
            }
            return add;
        }
    }
}