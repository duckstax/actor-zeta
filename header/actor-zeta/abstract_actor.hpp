#pragma once

#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>
#include <communication_module.hpp>

namespace actor_zeta {
    ///
    /// @brief Abstract concept of an actor
    ///

    class abstract_actor :  communication_module {
    public:
        ~abstract_actor() override;

        address_t address() const noexcept;

        auto enqueue(message) -> void;

        void enqueue(message, executor::execution_device*);

        auto name() const -> detail::string_view {
            return name_;
        }

    protected:
        explicit abstract_actor(detail::string_view);

        virtual void enqueue_base(message, executor::execution_device*) = 0;

    private:
        abstract_actor(const abstract_actor&) = delete;
        abstract_actor& operator=(const abstract_actor&) = delete;
    };

}// namespace actor_zeta::base
