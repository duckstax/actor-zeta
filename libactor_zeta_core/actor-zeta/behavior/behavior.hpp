#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <unordered_map>
#include <vector>

#include "actor-zeta/forwards.hpp"
#include "action.hpp"
#include "type_action.hpp"

namespace actor_zeta {
    namespace behavior {
///
/// @brief An actor's dispatcher
///
        class behavior final {
        public:
            behavior() = default;

            behavior(const behavior &) = delete;

            behavior &operator=(const behavior &) = delete;

            behavior(behavior &&) = default;

            behavior &operator=(behavior &&) = default;

            ~behavior() = default;

            void insert(abstract_action *aa);

            response *run(request *);
        private:
            std::unordered_map<type_action, action> behavioral_reactions;
        };
    }
}

#endif //BEHAVIOR_HPP
