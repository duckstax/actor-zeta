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

            template<std::size_t N>
            basic_actor(
                    supervisor *ptr,
                    const char(&name)[N]
            ): actor_type(ptr, new MailBox, detail::string_view(name)) {

            }

            virtual ~basic_actor() = default;

        };

        using basic_async_actor = basic_actor<messaging::blocking_mail_queue>;

}}
