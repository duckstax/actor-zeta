#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/message.hpp>
#include <communication_module.hpp>

namespace actor_zeta {

    class supervisor;

    class abstract_supervisor : public communication_module {
    public:
        abstract_supervisor(detail::string_view);

        abstract_supervisor(supervisor, detail::string_view);

        ~abstract_supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto join(actor) -> address_t = 0;

        virtual auto join(supervisor) -> address_t = 0;

        using communication_module::broadcast;

        auto address() -> address_t {
            return address_t(this);
        }

        auto name() -> detail::string_view {
            return name_;
        }

        auto enqueue(message) -> void;

        void enqueue(message, executor::execution_device*);

    protected:
        auto set_current_message(message) -> void;
        auto current_message() -> message&;

        virtual void enqueue_base(message, executor::execution_device*) = 0;

    private:
        message current_message_;
    };

    template<class T>
    auto spawn() -> void {
    }

} // namespace actor_zeta