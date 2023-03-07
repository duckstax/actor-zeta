#pragma once

#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/cooperative_actor.hpp>

namespace actor_zeta { namespace base {

    /**
     * @brief A generic actor
     *
     * @tparam actor_traits
     */
    template<typename actor_traits>
    using basic_async_actor = cooperative_actor<actor_traits>;

}} // namespace actor_zeta::base
