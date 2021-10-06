#pragma once

#include "send.hpp"

namespace actor_zeta {

    namespace detail {
        void link_imp(base::address_t a1, base::address_t a2);
    }

   // template<class Actor>
    //void link(basic_async_actor& actor1, basic_async_actor& actor2);

    template<class Supervisor>
    void link(Supervisor* actor1, Supervisor* actor2) {
        detail::link_imp(actor1->address(), actor2->address());
    }

    template<class Supervisor>
    void link(Supervisor& actor1, Supervisor& actor2) {
        detail::link_imp( actor1.address(), actor2.address());
    }

    template<class Supervisor>
    void link(Supervisor& actor1, base::address_t& actor2) {
        detail::link_imp(actor1.address(), actor2);
    }

    void link(base::address_t actor1, base::address_t actor2);

} // namespace actor_zeta
