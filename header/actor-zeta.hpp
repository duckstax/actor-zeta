#pragma once

// clang-format off
#include <handler.hpp>
#include <actor-zeta/address_t.hpp>
#include <message.hpp>
#include <basic_actor.hpp>
#include <abstract_supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

namespace actor_zeta {

    using abstract_actor;
    using abstract_supervisor;
    using actor;
    using address_type;
    using basic_async_actor;
    using make_handler;
    using supervisor;

    using executor::abstract_executor;
    using executor::executable;
    using executor::execution_device;
    using executor::executor_t;
    using executor::work_sharing;

    using message;

    template<class T>
    auto make_message(address_type sender_, T name) -> message {
        return message(std::move(sender_), std::forward<T>(name));
    }

    template<class T, typename Arg>
    auto make_message(address_type sender_, T name, Arg&& arg) -> message {
        return message(std::move(sender_), std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<class T, typename... Args>
    auto make_message(address_type sender_, T name, Args&&... args) -> message {
        return message(sender_, std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...})));
    }

    template<
        typename Actor,
        typename Supervisor,
        typename... Args>
    auto join(Supervisor& supervisor, Args&&... args) -> actor_zeta::address_type {
        return supervisor->join(new Actor(supervisor, std::forward<Args>(args)...));
    }

    template<typename Sender, typename... Args>
    void send(Sender& a1, Args... args) {
        a1->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename Sender, typename... Args>
    void send(const Sender& a1, Args... args) {
        a1->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<class Sender>
    void send(const Sender& actor, message msg) {
        actor->enqueue(std::move(msg));
    }

    template<class Sender>
    void send(Sender&& actor, message msg) {
        actor->enqueue(std::move(msg));
    }

    inline void link_imp(actor_zeta::address_type& a1, actor_zeta::address_type& a2) {
        send(a1, a2, "add_link", a2);
        send(a2, a1, "add_link", a1);
    }

    inline void link(basic_async_actor& actor1, basic_async_actor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor* actor1, Supervisor* actor2) {
        auto a1 = actor1->address_type();
        auto a2 = actor2->address_type();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, Supervisor& actor2) {
        auto a1 = actor1->address_type();
        auto a2 = actor2->address_type();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, address_type& actor2) {
        auto a1 = actor1->address_type();
        auto a2 = actor2->address();
        link_imp(a1, a2);
    }

    inline void link(address_type& actor1, address_type& actor2) {
        link_imp(actor1, actor2);
    }
} // namespace actor_zeta