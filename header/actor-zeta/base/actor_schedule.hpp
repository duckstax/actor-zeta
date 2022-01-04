#pragma once

#include <actor-zeta/base/actor_cooperative.hpp>

namespace actor_zeta { namespace base {

    template<class Actor>
    class actor_schedule : public actor_cooperative_t {
    public:
        using self_t = actor_schedule<Actor>;
        using self_pointer = self_t*;

    protected:
        template<class Supervisor>
        actor_schedule(Supervisor* ptr, std::string type, int64_t actor_id)
            : actor_cooperative_t(static_cast<supervisor_abstract*>(ptr), std::move(type), actor_id){};

        template<class F>
        void behavior(const F&f){
            behavior_t tmp(this);
            f(tmp);
            behavior_.assign(tmp);
        }

        /// ----- deprecated

        template<class F>
        auto add_handler(behavior_t::key_type name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            behavior_.on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(behavior_t::key_type name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            behavior_.on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        template<class T,typename F>
        auto add_handler(behavior_t::key_type name,T*ptr, F&& f) -> void{
            behavior_.on(name, make_handler(std::forward<F>(f), ptr));
        }

        /// ----- deprecated

    };

}} // namespace actor_zeta::base