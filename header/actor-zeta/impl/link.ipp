#pragma once

#include "actor-zeta/link.hpp"

namespace actor_zeta {
    namespace detail {
        void link_imp(base::address_t& a1, base::address_t& a2) {
            send(a1, a2, "add_link");
            send(a2, a1, "add_link");
        }
    }
/*
    void link(basic_async_actor& actor1, basic_async_actor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        detail::link_imp(a1, a2);
    }
*/
    void link(base::address_t& actor1, base::address_t& actor2) {
        detail::link_imp(actor1, actor2);
    }
}