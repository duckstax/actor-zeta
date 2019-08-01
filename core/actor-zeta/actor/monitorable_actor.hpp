#pragma once

#include <memory>
#include <unordered_map>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/base_actor.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief A generic actor
///
        class monitorable_actor : public base_actor {
        public:
            virtual void launch(executor::execution_device*, bool /*hide*/) = 0;

            ~monitorable_actor() override ;

        protected:

            auto attach(executor::execution_device *) -> void;

            auto attach() const -> executor::execution_device* ;

            monitorable_actor(supervisor *, detail::string_view);

            auto env() -> supervisor* ;

            /// sync -> async
            void add_link(actor_address);
            /// sync -> async
            void remove_link(const actor_address&);
            /// sync -> async
            void remove_link(detail::string_view);

        private:
            void initialize();

            supervisor* supervisor_;
            executor::execution_device *executor_;
        };
}}
