#pragma once

#include "actor-zeta/behavior/abstract_action.hpp"

namespace actor_zeta {
///
/// @brief
///
    class sync_contacts final : public behavior::abstract_action {
    public:
        sync_contacts();

        void invoke(behavior::context &) override final;

    };
}
