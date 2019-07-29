#pragma once

#include <unordered_map>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/detail/storage_space.hpp>
#include <actor-zeta/actor/supervisor.hpp>
#include <actor-zeta/actor/actor.hpp>


namespace actor_zeta { namespace environment {
        using messaging::message;
///
/// @brief
///
        class supervisor_heavy : public actor::supervisor {
        public:
            explicit supervisor_heavy(abstract_environment*);

            ~supervisor_heavy() override = default;

            auto id() const -> id_t;

            auto join(actor::abstract_actor *t) -> actor_zeta::actor::actor;

            template<typename Actor, typename Supervisor, typename... Args>
            auto join(Supervisor& supervisor, Args... args) -> actor_zeta::actor::actor {
                return join(new Actor(supervisor, std::forward<Args>(args)...));
            }

            void add_shared(const actor::actor_address &);

            auto entry_point() -> actor::actor_address override;

            auto join(supervisor &) -> void override;

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