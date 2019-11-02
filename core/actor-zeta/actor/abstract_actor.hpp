#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/message_passing_interface.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Abstract concept of an actor
///

        class abstract_actor : public message_passing_interface  {
        public:
            abstract_actor()= delete;

            abstract_actor(const abstract_actor &) = delete;

            abstract_actor &operator=(const abstract_actor &) = delete;

            ~abstract_actor() override;

            explicit abstract_actor(detail::string_view);

            /// sync -> async
            void add_link(actor_address);
            /// sync -> async
            void remove_link(const actor_address&);
            /// sync -> async
            void remove_link(detail::string_view);

        protected:
            void initialize();
        };

}}
