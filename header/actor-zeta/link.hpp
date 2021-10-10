#pragma once

#include "send.hpp"

namespace actor_zeta {

    namespace detail {
        void link_imp(base::address_t& a1, base::address_t& a2);
    }

   // template<class Actor>
    //void link(basic_async_actor& actor1, basic_async_actor& actor2);

    template<class Supervisor>
    void link(Supervisor* actor1, Supervisor* actor2) {
        auto a1 = actor1->address();
        auto a2 = actor2->address();
        detail::link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, Supervisor& actor2) {
        auto a1 = actor1.address();
        auto a2 = actor2.address();
        detail::link_imp(a1, a2);
    }

    template<class Supervisor>
    void link(Supervisor& actor1, base::address_t& actor2) {
        auto a1 = actor1.address();
        detail::link_imp(a1, actor2);
    }

    void link(base::address_t& actor1, base::address_t& actor2);

} // namespace actor_zeta
