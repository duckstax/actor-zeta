#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/communication_module.hpp>

namespace actor_zeta { namespace base {

    class supervisor : public communication_module {
    public:
        supervisor(detail::string_view);

        ~supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto join(actor) -> actor_address = 0;

        ///using communication_module::broadcast;

    protected:
        auto set_current_message(message_ptr) -> void;

    private:
        message* current_message_;
        auto current_message  () -> message* final;
    };

}}