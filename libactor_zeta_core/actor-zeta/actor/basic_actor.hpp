#ifndef BASIC_ACTOR_HPP
#define BASIC_ACTOR_HPP

#include <actor-zeta/actor/scheduled_actor.hpp>
#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/behavior/fsm.hpp>

namespace actor_zeta { namespace actor {

        template<
                typename MailBox,
                typename Behavior,
                typename Actor = scheduled_actor
        >
        class basic_actor : public Actor {
        public:
            virtual ~basic_actor() = default;
            basic_actor(
                    environment::abstract_environment *ptr,
                    const std::string &name
            )
                    : Actor(ptr, new MailBox, new Behavior, name) {

            }

        };

        using basic_scheduled_actor = basic_actor<messaging::blocking_mail_queue,behavior::behavior_fsm>;

        template<
                typename MailBox,
                typename Behavior,
                typename Actor = scheduled_actor
        >
        actor make_actor(environment::abstract_environment *ptr, const std::string &name) {
            return new basic_actor<MailBox,Behavior,Actor>(ptr,name);
        };
    }
}
#endif
