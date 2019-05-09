#pragma once

#include <actor-zeta/actor/async_actor.hpp>
#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/messaging/blocking_mail_queue.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief
///
        template<
                typename MailBox,
                typename Actor = async_actor
        >
        class basic_actor : public Actor {
        public:
            using actor_type = Actor;

            template<std::size_t N>
            basic_actor(
                    environment::abstract_environment *ptr,
                    const char(&name)[N]
            ): actor_type(ptr, new MailBox, name) {

            }

            virtual ~basic_actor() = default;

        };

        using basic_async_actor = basic_actor<messaging::blocking_mail_queue>;

        template<
                typename MailBox,
                typename Actor = async_actor
        >
        actor make_actor(environment::abstract_environment *ptr, const std::string &name) {
            return new basic_actor<MailBox,Actor>(ptr,name);
        }
    }
}
