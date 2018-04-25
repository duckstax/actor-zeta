#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <unordered_map>
#include <stack>


#include <actor-zeta/behavior/type_action.hpp>
#include <actor-zeta/behavior/abstract_behavior.hpp>
#include <actor-zeta/behavior/abstract_action.hpp>

namespace actor_zeta { namespace behavior {
///
/// @brief
///

        class behavior_fsm final : public abstract_behavior {
        public:
            behavior_fsm() = default;

            behavior_fsm(const behavior_fsm &) = delete;

            behavior_fsm &operator=(const behavior_fsm &) = delete;

            behavior_fsm(behavior_fsm &&) = delete;

            behavior_fsm &operator=(behavior_fsm &&) = delete;

            ~behavior_fsm() override = default;

            bool insert(abstract_action *aa) override ;

            void run(context &) override ;

        private:
            std::unordered_map<event_type, std::unique_ptr<abstract_action>> behavioral_reactions;
        };

    } /// namespace behavior
} /// namespace actor_zeta

#endif //BEHAVIOR_HPP
