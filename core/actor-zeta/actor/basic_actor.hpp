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
                    supervisor *ptr,
                    detail::string_view name
            ): actor_type(ptr, new MailBox, name) {

            }

            virtual ~basic_actor() = default;

        };

        using basic_async_actor = basic_actor<messaging::blocking_mail_queue>;

        template<
                typename MailBox,
                typename Actor = cooperative_actor
        >
        inline actor make_actor(supervisor *ptr, const std::string &name) {
            return new basic_actor<MailBox,Actor>(ptr,name);
        }

        template<typename Actor,typename... Args>
        inline void send(Actor&a1,Args... args){
            a1->enqueue(
                    messaging::make_message(
                            std::forward<Args>(args)...
                    )
            );
        }

        template<typename Actor,typename... Args>
        inline void send(const Actor&a1,Args... args){
            a1->enqueue(
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

}}
