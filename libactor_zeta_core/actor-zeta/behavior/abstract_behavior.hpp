#ifndef ABSTRACT_BEHAVIOR_HPP
#define ABSTRACT_BEHAVIOR_HPP

#include <actor-zeta/behavior/context.hpp>

namespace actor_zeta {
    namespace behavior {

        struct abstract_behavior {

            using event_type = type_action;

            abstract_behavior() = default;

            abstract_behavior(const abstract_behavior &) = delete;

            abstract_behavior &operator=(const abstract_behavior &) = delete;

            abstract_behavior(abstract_behavior &&) = delete;

            abstract_behavior &operator=(abstract_behavior &&) = delete;

            virtual ~abstract_behavior() = default;

            virtual bool insert(abstract_action *aa) = 0;

            virtual void run(context &)              = 0;
        };       

    }
}
#endif //
