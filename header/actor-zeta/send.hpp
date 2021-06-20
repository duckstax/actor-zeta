#pragma once

#include <actor-zeta/make_message.hpp>

namespace actor_zeta {

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