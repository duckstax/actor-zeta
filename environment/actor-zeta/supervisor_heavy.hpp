#pragma once

#include <unordered_map>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/detail/storage_space.hpp>
#include <actor-zeta/actor/supervisor.hpp>


namespace actor_zeta { namespace environment {
        using messaging::message;
///
/// @brief
///
        class supervisor_heavy : public actor::supervisor {
        public:
            supervisor_heavy(abstract_environment*,detail::storage_space ss, actor::abstract_actor *t);

            ~supervisor_heavy() override = default;

            auto id() const -> id_t;

            void add(actor::abstract_actor *);

            void add_shared(const actor::actor_address &);

            auto entry_point() -> actor::actor_address override;

            auto join(supervisor &) -> void override;

            auto send(messaging::message) -> bool override;

            bool send(messaging::message, executor::execution_device *) override;

            auto broadcast(messaging::message) -> bool override;

            auto shutdown() noexcept -> void override ;

            auto startup() noexcept -> void override ;

            auto executor() noexcept -> executor::abstract_executor& override;

        protected:
            std::size_t cursor;
            detail::storage_space storage_space_;
            id_t entry_point_;
            detail::layer shared_point;
            abstract_environment* env_;

        };

}}