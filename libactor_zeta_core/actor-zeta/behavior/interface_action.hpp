#ifndef ABSTRACT_ACTION_HPP
#define ABSTRACT_ACTION_HPP

#include <string>

#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace behavior {
        struct interface_action {
            virtual void operator()(messaging::message *) = 0;

            virtual const std::string &name() const = 0;

            virtual ~interface_action() {}
        };
    }
}
#endif
