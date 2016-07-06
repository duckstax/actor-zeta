#ifndef ABSTRACT_ACTION_HPP
#define ABSTRACT_ACTION_HPP

#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace behavior {
        struct abstract_action {
            virtual void operator()(messaging::message &&msg)=0;

            virtual const std::string name() const =0;

            virtual ~abstract_action() {}
        };
    }
}
#endif
