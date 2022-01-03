#pragma once

#include <actor-zeta/base/cooperative_actor.hpp>

namespace actor_zeta { namespace base {

    template<class Actor>
    class actor_schedule : public cooperative_actor {
    public:
        using self_t = actor_schedule<Actor>;
        using self_pointer = self_t*;

    protected:
        template<class Supervisor>
        actor_schedule(Supervisor* ptr, std::string type, int64_t actor_id)
            : cooperative_actor(ptr, std::move(type), actor_id) {
        }

        template<class F>
        void behavior(const F&f){
            behavior_t tmp(this);
            f(tmp);
            behavior_.assign(std::move(tmp.get()));
        }
    };

}} // namespace actor_zeta::base