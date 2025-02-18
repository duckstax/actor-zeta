#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/make_message.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>

namespace actor_zeta {

    template<typename... Args>
    void send(base::actor_abstract* actor, Args... args) {
        actor->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

    template<typename... Args>
    void send(base::address_t& address, Args... args) {
        address->enqueue(
            make_message(
                std::forward<Args>(args)...));
    }

} // namespace actor_zeta
