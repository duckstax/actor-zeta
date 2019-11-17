#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/communication_module.hpp>

namespace actor_zeta { namespace actor {

    using messaging::message;

    class supervisor : public communication_module {
    public:
        supervisor(detail::string_view);

        ~supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto join(abstract_actor *) -> actor_zeta::actor::actor_address = 0;

        using communication_module::broadcast;
    protected:
        auto set_current_message(messaging::message) -> void;
    private:
        messaging::message current_message_;
        auto current_message  () -> messaging::message& final;

    };

}}