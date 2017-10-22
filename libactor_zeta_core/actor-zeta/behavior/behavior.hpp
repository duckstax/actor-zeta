#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <unordered_map>
#include <vector>

#include "actor-zeta/forwards.hpp"
#include "action.hpp"
#include "type_action.hpp"
#include "actor-zeta/behavior/abstract_behavior.hpp"

namespace actor_zeta {
    namespace behavior {
///
/// @brief
///

        class behavior final : public abstract_behavior {
        public:
            behavior() = default;

            behavior(const behavior &) = delete;

            behavior &operator=(const behavior &) = delete;

            behavior(behavior &&) = delete;

            behavior &operator=(behavior &&) = delete;

            ~behavior() = default;

            bool insert(abstract_action *aa) override ;

            response run(request &&) override ;

        private:
            std::unordered_map<type_action, action> behavioral_reactions;
        };
    }
}

#endif //BEHAVIOR_HPP
