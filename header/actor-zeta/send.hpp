#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>

#include <actor-zeta/make_message.hpp>

namespace actor_zeta {

    template<class Supervisor, typename... Args>
    void send(Supervisor& supervisor, Args... args) {
        supervisor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<class Supervisor, typename... Args>
    void send(const Supervisor& supervisor, Args... args) {
        supervisor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename... Args>
    void send(base::actor& actor, Args... args) {
        actor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename... Args>
    void send(base::actor&& actor, Args... args) {
        actor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename... Args>
    void send(base::address_t&& address, Args... args) {
        address->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename... Args>
    void send(base::address_t& address, Args... args) {
        address->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    void send(base::address_t address, base::message_ptr msg);

} // namespace actor_zeta
