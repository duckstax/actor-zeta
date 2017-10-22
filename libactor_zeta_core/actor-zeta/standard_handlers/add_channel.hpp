#ifndef ADD_CHANNEL_HPP
#define ADD_CHANNEL_HPP

#include "actor-zeta/behavior/abstract_action.hpp"

namespace actor_zeta {
///
/// @brief 
///
    class add_channel final : public behavior::abstract_action {
    public:
        add_channel();

        behavior::response operator()(behavior::request &&) override final;

    };
}
#endif //ADD_CHANNEL_HPP
