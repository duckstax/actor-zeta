#pragma once

#include <functional>

#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an action
    ///

    using handler = std::function<void()>;

    template<typename Context, typename F>
    auto make_handler_base(Context&& ctx, F&& f) -> handler*;

    template<typename Context, typename F, typename ClassPtr>
    auto make_handler_base(Context&& ctx, F&& f, ClassPtr* self) -> handler*;

    template<typename Context, typename F>
    auto make_handler(Context&& ctx, F&& f) -> handler* {
        return  make_handler_base<Context,F>(std::forward<Context>(ctx), std::forward<F>(f));
    }

    template<typename Context, typename F, typename ClassPtr>
    auto make_handler(Context&& ctx, F&& f, ClassPtr* self) -> handler* {
        return make_handler_base<Context,F,ClassPtr>(std::forward<Context>(ctx), std::forward<F>(f), self);
    }

}} // namespace actor_zeta::base
