#pragma once

#include <actor-zeta/actor/executable_actor.hpp>
#include <actor-zeta/actor/message_passing_interface.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace actor {

    using messaging::message;

    class supervisor : public message_passing_interface {
    public:
        supervisor(detail::string_view);

        ~supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto broadcast(message) -> bool = 0;

        virtual auto join(abstract_actor *) -> actor_zeta::actor::actor_address = 0;

    };

}}