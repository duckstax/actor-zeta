#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    class supervisor_t : public communication_module {
    public:
        supervisor_t(std::string);

        ~supervisor_t() override;

        virtual auto executor() noexcept -> executor::abstract_executor* = 0;

        virtual auto join(actor) -> actor_address = 0;

        using communication_module::broadcast;

    protected:
        auto set_current_message(message_ptr) -> void;
        auto current_message() -> message* final;

    private:
        message* current_message_;
    };

}} // namespace actor_zeta::base