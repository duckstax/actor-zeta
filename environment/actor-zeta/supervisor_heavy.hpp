#pragma once

#include <unordered_map>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/detail/storage_space.hpp>
#include <actor-zeta/actor/supervisor.hpp>
#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/actor/executable_actor.hpp>


namespace actor_zeta { namespace environment {
        using messaging::message;
///
/// @brief
///
        class supervisor_heavy : public actor::supervisor {
        public:
            explicit supervisor_heavy(abstract_environment*,char const*);

            ~supervisor_heavy() override = default;

            auto id() const -> id_t;

            void add_shared(const actor::actor_address &);

            using supervisor::join;

            auto join(actor::base_actor *) -> actor_zeta::actor::actor_address final;

            auto join(supervisor &) -> void override;

            void enqueue(messaging::message, executor::execution_device *) final;

            auto broadcast(messaging::message) -> bool override;

            auto shutdown() noexcept -> void override ;

            auto startup() noexcept -> void override ;

            auto executor() noexcept -> executor::abstract_executor& final;

        protected:
            std::size_t cursor;
            detail::storage_space storage_space_;
            id_t entry_point_;
            detail::layer shared_point;
            abstract_environment* env_;

        };

}}