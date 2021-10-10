#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta {

    template<class T>
    auto make_message_ptr(base::address_t sender_, T name) -> base::message* {
        return new base::message(std::move(sender_), std::forward<T>(name));
    }

    template<class T, typename Arg>
    auto make_message_ptr(base::address_t sender_, T name, Arg&& arg) -> base::message* {
        return new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<class T, typename... Args>
    auto make_message_ptr(base::address_t sender_, T name, Args&&... args) -> base::message* {
        return new base::message(sender_, std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...})));
    }

    template<class T>
    auto make_message(base::address_t sender_, T name) -> base::message_ptr {
        return base::message_ptr(new base::message(std::move(sender_), std::forward<T>(name)));
    }

    template<class T, typename Arg>
    auto make_message(base::address_t sender_, T name, Arg&& arg) -> base::message_ptr {
        return base::message_ptr(new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg)))));
    }

    template<class T, typename... Args>
    auto make_message(base::address_t sender_, T name, Args&&... args) -> base::message_ptr {
        return base::message_ptr(new base::message(sender_, std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...}))));
    }

} // namespace actor_zeta