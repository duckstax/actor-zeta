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
                    supervisor &ptr,
                    const char(&name)[N]
            ): actor_type(ptr, new MailBox, detail::string_view(name)) {

            }

            virtual ~basic_actor() = default;

        };

        using basic_async_actor = basic_actor<messaging::blocking_mail_queue>;

        template<
                typename MailBox,
                typename Actor = async_actor
        >
        inline actor make_actor(supervisor *ptr, const std::string &name) {
            return new basic_actor<MailBox,Actor>(ptr,name);
        }

        template<typename Actor,typename... Args>
        inline void send(Actor&a1,Args... args){
            a1->send(
                    messaging::make_message(
                            std::forward<Args>(args)...
                    )
            );
        }

        inline void link_imp(const actor_address& a1,const actor_address& a2 ){
            send(a1,a2,"sync_contacts",a2);
            send(a2,a1,"sync_contacts",a1);
        }

        template <typename Actor1, typename Actor2>
        inline void link(Actor1&actor1,Actor2&actor2){
            link_imp(actor1->address(),actor2->address());
        }

    }
}
