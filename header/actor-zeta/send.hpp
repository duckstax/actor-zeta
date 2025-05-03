#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <actor-zeta/make_message.hpp>

namespace actor_zeta {

    template<typename... Args>
    void send(base::actor_abstract_t* actor, Args... args) {
        actor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<class Actor>
    void send(Actor* actor, message_ptr ptr) {
        actor->enqueue(std::move(ptr));
    }

    void send(base::actor_abstract_t* actor, message_ptr ptr);

    template<typename... Args>
    void send(base::address_t& address, Args... args) {
        address->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

} // namespace actor_zeta
