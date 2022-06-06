#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/unique_function.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an action
    ///

    using action = detail::unique_function<void(mailbox::message*)>;

    template<typename F>
    auto make_handler(F&& f)-> action ;

    template<typename F, typename ClassPtr>
    auto make_handler(F&& f, ClassPtr* self) -> action ;

}} // namespace actor_zeta::base
