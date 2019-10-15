#pragma once

#include <actor-zeta/actor/cooperative_actor.hpp>
#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/messaging/blocking_mail_queue.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief A generic actor
///
        template<
                typename MailBox,
                typename Actor = cooperative_actor
        >
        class basic_actor : public Actor {
        public:
            using actor_type = Actor;

            basic_actor(
                    supervisor &ptr,
                    detail::string_view name
            ): actor_type(ptr, new MailBox, name) {

            }

            virtual ~basic_actor() = default;

        };

        using basic_async_actor = basic_actor<messaging::blocking_mail_queue>;

}}
