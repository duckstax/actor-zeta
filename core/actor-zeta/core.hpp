#pragma once

// clang-format off
#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/basic_actor.hpp>
#include <actor-zeta/actor/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

namespace actor_zeta {

    using actor::abstract_actor;
    using actor::context;
    using actor::basic_async_actor;
    using actor::actor_address;
    using actor::context;
    using actor::supervisor;
    using actor::make_handler;

    using executor::executor_t;
    using executor::work_sharing;
    using executor::abstract_executor;
    using executor::executable;
    using executor::execution_device;

    using messaging::message;

    template<class T>
    inline auto make_message(actor::actor_address sender_, T name) -> message {
        return message(std::move(sender_),std::forward<T>(name));
    }

    template<class T,typename Arg>
    inline auto make_message(actor::actor_address sender_, T name,Arg&& arg) -> message {
        return message(std::move(sender_),std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<class T, typename... Args>
    inline auto make_message(actor::actor_address sender_,T name,Args&&... args) -> message {
        return message(sender_,std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...})));
    }

    template<
            typename Actor,
            typename Supervisor,
            typename... Args
    >
    inline auto make_actor(Supervisor& supervisor, Args&&... args) -> actor_zeta::actor::actor_address {
        return supervisor.join(new Actor(supervisor, std::forward<Args>(args)...));
    }

    template<typename Sender, typename... Args>
    inline void send(Sender& a1, Args... args) {
        a1->enqueue(
                make_message(
                        std::forward<Args>(args)...
                )
        );
    }

    template<typename Sender, typename... Args>
    inline void send(const Sender& a1, Args... args) {
        a1->enqueue(
                make_message(
                        std::forward<Args>(args)...
                )
        );
    }

    template<class Sender>
    inline void send(const Sender& actor, message msg) {
        actor->enqueue(std::move(msg));
    }

    template<class Sender>
    inline void send(Sender& actor, message msg) {
        actor->enqueue(std::move(msg));
    }

    inline void link_imp(actor_zeta::actor_address& a1,actor_zeta::actor_address& a2) {
        send(a1,a2,"sync_contacts",a2);
        send(a2,a1,"sync_contacts",a1);
    }

    inline void link(basic_async_actor& actor1,basic_async_actor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        link_imp(a1,a2);
    }

    template <class Supervisor>
    inline void link(Supervisor* actor1,Supervisor* actor2) {
        auto a1 = actor1->address();
        auto a2 = actor2->address();
        link_imp(a1,a2);
    }

    template <class Supervisor>
    inline void link(Supervisor& actor1,Supervisor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        link_imp(a1,a2);
    }

    template <class Supervisor>
    inline void link(Supervisor& actor1,actor_address& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2->address();
        link_imp(a1,a2);
    }

    inline void link(actor_address &actor1,actor_address&actor2) {
        link_imp(actor1,actor2);
    }


    
}