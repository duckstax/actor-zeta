#pragma once

#include <actor-zeta/make_message.hpp>

namespace actor_zeta {

    template<
        typename Sender,
        typename... Args>
    void broadcast(Sender& a1, Args... args) {
        a1->broadcast(
            make_message(
                std::forward<Args>(args)...));
    }

} // namespace actor_zeta