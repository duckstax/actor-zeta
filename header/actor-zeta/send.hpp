#pragma once

#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/make_message.hpp>

namespace actor_zeta {

    template<typename... Args>
    void send(base::supervisor& supervisor, Args... args) {
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
    void send(base::address_t address, Args... args) {
        address.enqueue(
            make_message(
                std::forward<Args>(args)...));
    }
/*
    template<typename... Args>
    void send(base::address_t& address,base::address_t& address2, Args... args) {
        address.enqueue(
            make_message(address2,
                std::forward<Args>(args)...));
    }
*/
    template<typename... Args>
    void send(const base::supervisor& supervisor, Args... args) {
        supervisor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename... Args>
    void send( base::actor&& actor, Args... args) {
        actor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }
/*
    template<typename... Args>
    void send(const base::address_t& address, Args... args) {
        address.enqueue(
            make_message(
                std::forward<Args>(args)...));
    }
*/
} // namespace actor_zet