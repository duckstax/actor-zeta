#ifndef SKIP_HPP
#define SKIP_HPP

#include <string>

#include "actor-zeta/behavior/abstract_action.hpp"

namespace actor_zeta {
///
/// @brief
///
    class skip final : public behavior::abstract_action {
    public:
        skip();

        behavior::response operator()(behavior::request &&) override final;
    };
}
#endif //SKIP_HPP
