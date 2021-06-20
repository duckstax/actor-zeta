#pragma once

#include "send.hpp"

namespace actor_zeta {

    inline void link_imp(actor_address& a1, actor_address& a2) {
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
        auto a1 = actor1->address();
        auto a2 = actor2->address();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, Supervisor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, actor_address& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2->address();
        link_imp(a1, a2);
    }

    inline void link(actor_address& actor1, actor_address& actor2) {
        link_imp(actor1, actor2);
    }

} // namespace actor_zeta