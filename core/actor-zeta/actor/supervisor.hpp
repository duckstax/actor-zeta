#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/message_passing_interface.hpp>

namespace actor_zeta { namespace actor {

    using messaging::message;

    class supervisor : public message_passing_interface {
    public:
        supervisor(detail::string_view);

        ~supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto join(abstract_actor *) -> actor_zeta::actor::actor_address = 0;

        using message_passing_interface::broadcast;
    protected:
        auto set_current_message(messaging::message) -> void;
    private:
        messaging::message current_message_;
        auto current_message  () -> messaging::message& final;

    };

}}