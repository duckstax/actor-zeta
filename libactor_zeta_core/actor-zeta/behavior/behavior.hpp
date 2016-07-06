#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include "actor-zeta/forwards.hpp"
#include "action.hpp"

namespace actor_zeta {
    namespace behavior {
        class behavior {
        public:
            behavior() = default;

            behavior(behavior &&) = default;

            behavior(const behavior &) = delete;

            behavior &operator=(behavior &&) = default;

            behavior &operator=(const behavior &) = delete;

            ~behavior() = default;

            void insert(abstract_action *aa);

            void run(messaging::message &&);

            //debug method
            void all_name_view();

        private:
            std::unordered_map<std::string, action> behavioral_reactions;
        };
    }
}

#endif //BEHAVIOR_HPP
