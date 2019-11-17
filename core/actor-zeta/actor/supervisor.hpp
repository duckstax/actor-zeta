#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/abstract_async_container.hpp>

namespace actor_zeta { namespace actor {

    using messaging::message;

    class supervisor : public abstract_async_container {
    public:
        supervisor(detail::string_view);

        ~supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto join(abstract_actor *) -> actor_zeta::actor::actor_address = 0;

        using abstract_async_container::broadcast;
    protected:
        auto set_current_message(messaging::message) -> void;
    private:
        messaging::message current_message_;
        auto current_message  () -> messaging::message& final;

    };

}}