#pragma once

#include <actor-zeta/actor/executable_actor.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace actor {

    using messaging::message;

    class supervisor : public base_actor {
    public:
        supervisor(detail::string_view);

        ~supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto broadcast(message) -> bool = 0;

        virtual auto join(base_actor *t) -> actor_zeta::actor::actor_address = 0;

        virtual auto join(supervisor &) -> void = 0;
    };

    auto link(supervisor &g1, supervisor &g2) -> void;

}}