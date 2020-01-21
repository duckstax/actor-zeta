#pragma once

#include <actor-zeta/base/cooperative_actor.hpp>
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/messaging/blocking_mail_queue.hpp>

namespace actor_zeta { namespace base {

///
/// @brief A generic base
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
            ): actor_type(ptr, name, new MailBox) {

            }

            virtual ~basic_actor() = default;

        };

        using basic_async_actor = basic_actor<messaging::blocking_mail_queue>;

}}
