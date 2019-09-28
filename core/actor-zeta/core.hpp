#pragma once

#include <actor-zeta/actor/basic_actor.hpp>
#include <actor-zeta/actor/supervisor.hpp>

#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

namespace actor_zeta {

    using actor::context;
    using actor::basic_async_actor;
    using actor::actor_address;
    using actor::context;
    using actor::basic_async_actor;
    using actor::supervisor;

    using executor::executor_t;
    using executor::work_sharing;
    using executor::abstract_executor;
    using executor::executable;

    using messaging::message;
    using messaging::make_message;

    template<
            typename MailBox,
            typename Actor = actor::cooperative_actor
    >
    inline auto  make_actor(supervisor *ptr, const std::string &name) -> actor::actor {
        return new actor::basic_actor<MailBox,Actor>(ptr,name);
    }

    template<
            typename Actor,
            typename Supervisor,
            typename... Args
    >
    inline auto make_actor(Supervisor* supervisor, Args... args) -> actor_zeta::actor::actor_address {
        return supervisor->join(new Actor(supervisor, std::forward<Args>(args)...));
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

    inline auto link_imp(actor_zeta::actor_address&a1,actor_zeta::actor_address&a2) -> void {
        send(a1,a2,"sync_contacts",a2);
        send(a2,a1,"sync_contacts",a1);
    }

    inline auto link(basic_async_actor &actor1,basic_async_actor &actor2) -> void {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        link_imp(a1,a2);
    }

    inline auto link(supervisor *actor1,supervisor *actor2) -> void {
        auto a1 = actor1->address();
        auto a2 = actor2->address();
        link_imp(a1,a2);
    }

    inline auto link(supervisor *actor1,actor_address&actor2) -> void {
        auto a1 = actor1->address();
        auto a2 = actor2->address();
        link_imp(a1,a2);
    }

    inline auto link(actor_address &actor1,actor_address&actor2) -> void {
        link_imp(actor1,actor2);
    }
    
}