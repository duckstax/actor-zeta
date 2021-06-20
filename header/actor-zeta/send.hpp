#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

namespace actor_zeta {

    using base::actor_abstract;
    using base::actor;
    using base::actor_address;
    using base::basic_async_actor;
    using base::make_handler;
    using base::supervisor;
    using base::supervisor_abstract;

    using executor::abstract_executor;
    using executor::executable;
    using executor::execution_device;
    using executor::executor_t;
    using executor::work_sharing;

    using base::message_ptr;

    template<class T>
    auto make_message(actor_address sender_, T name) -> message_ptr {
        return message_ptr(new base::message(std::move(sender_), std::forward<T>(name)));
    }

    template<class T, typename Arg>
    auto make_message(actor_address sender_, T name, Arg&& arg) -> message_ptr {
        return message_ptr(new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg)))));
    }

    template<class T, typename... Args>
    auto make_message(actor_address sender_, T name, Args&&... args) -> message_ptr {
        return message_ptr(new base::message(sender_, std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...}))));
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

    template<class Sender, class Message>
    void send(const Sender& actor, Message msg) {
        actor->enqueue(std::move(msg));
    }

    template<class Sender, class Message>
    void send(Sender& actor, Message msg) {
        actor->enqueue(std::move(msg));
    }
} // namespace actor_zeta