#pragma once
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/make_message.hpp>

namespace actor_zeta {

    template<
        typename Sender,
        typename... Args,
        class = type_traits::enable_if_t<std::is_base_of<base::supervisor, Sender>::value>>
    void broadcast(Sender& a1, Args... args) {
        a1->broadcast(
            make_message(
                std::forward<Args>(args)...));
    }

} // namespace actor_zeta