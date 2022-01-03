#pragma once

#include "forwards.hpp"
#include <actor-zeta/detail/unique_function.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an action
    ///

    using action = detail::unique_function<void(communication_module*)>;

    template<typename F>
    auto make_helper_base(F&& )-> action ;

    template<typename F, typename ClassPtr>
    auto  make_helper_base(F&& , ClassPtr* )->action ;

    template<typename F>
    auto make_handler(F&& f)-> action {
        return make_helper_base(std::forward<F>(f));
    }

    template<typename F, typename ClassPtr>
    auto make_handler(F&& f, ClassPtr* self) -> action {
        return make_helper_base(std::forward<F>(f), self);
    }

}} // namespace actor_zeta::base
