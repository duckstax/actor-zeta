#pragma once

#include <string>
#include <actor-zeta/forwards.hpp>
#include "actor-zeta/detail/ref_counted.hpp"
#include "../metadata.hpp"

namespace actor_zeta { namespace channel {
///
/// @brief
///

        struct abstract_channel : public ref_counted {
            virtual ~abstract_channel();

            virtual auto send(messaging::message &&)  -> bool      = 0;

            virtual auto broadcast(messaging::message &&) -> bool  = 0;

            auto type() const -> abstract ;

            auto name() const -> const std::string &;

            auto locating() const -> locations;

        protected:
            metadata type_;
        };
    }
}
