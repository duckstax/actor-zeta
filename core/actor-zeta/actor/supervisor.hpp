#pragma once

#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace actor {

    using messaging::message;

    class supervisor : public abstract_actor {
    public:
        ~supervisor() override = default;

        virtual auto shutdown() noexcept -> void = 0;

        virtual auto startup() noexcept -> void = 0;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto broadcast(message) -> bool = 0;

        virtual auto entry_point() -> actor_address = 0;

        virtual auto join(supervisor &) -> void = 0;
    };

    auto link(supervisor &g1, supervisor &g2) -> void;

}}