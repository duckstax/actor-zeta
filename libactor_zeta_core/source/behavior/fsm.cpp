#include <initializer_list>
#include <iostream>
#include <actor-zeta/behavior/fsm.hpp>
#include <actor-zeta/behavior/abstract_action.hpp>
#include <memory>

namespace actor_zeta {
    namespace behavior {

        void error(const std::string &_error_) {
            std::cerr << "Duplicate" << std::endl;
            std::cerr << "Handler: " << _error_ << std::endl;
            std::cerr << "Duplicate" << std::endl;
        }


        void behavior_fsm::run(context &d) {
            auto it = behavioral_reactions.find(d.state().message().command());
            if (it != behavioral_reactions.end()) {
                return it->second->invoke(d);
            }
            return behavioral_reactions.at("skip")->invoke(d);
        }

        bool behavior_fsm::insert(abstract_action *aa) {
            auto it = behavioral_reactions.emplace(aa->name(), std::unique_ptr<abstract_action>(aa));
            bool add = it.second;
            if (!add) {
                error(aa->name().to_string());
            }
            return add;
        }


    }
}
