#ifndef SKIP_HPP
#define SKIP_HPP

#include <string>

#include "actor-zeta/behavior/abstract_action.hpp"

namespace actor_zeta {
    class skip final : public behavior::abstract_action {
    public:
        skip();

        void operator()(messaging::message *msg) override final;
    };
}
#endif //SKIP_HPP
