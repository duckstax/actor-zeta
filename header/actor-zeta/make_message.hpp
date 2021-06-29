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

    using base::message;
    using base::address_t;
    using base::message_ptr;

    template<class T>
    auto make_message_ptr(address_t sender_, T name) -> message* {
        return new message(std::move(sender_), std::forward<T>(name));
    }

    template<class T, typename Arg>
    auto make_message_ptr(address_t sender_, T name, Arg&& arg) -> message* {
        return new message(std::move(sender_), std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<class T, typename... Args>
    auto make_message_ptr(address_t sender_, T name, Args&&... args) -> message* {
        return new message(sender_, std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...})));
    }

    template<class T>
    auto make_message(address_t sender_, T name) -> message_ptr {
        return message_ptr(new message(std::move(sender_), std::forward<T>(name)));
    }

    template<class T, typename Arg>
    auto make_message(address_t sender_, T name, Arg&& arg) -> message_ptr {
        return message_ptr(new message(std::move(sender_), std::forward<T>(name), std::move(detail::any(std::forward<type_traits::decay_t<Arg>>(arg)))));
    }

    template<class T, typename... Args>
    auto make_message(address_t sender_, T name, Args&&... args) -> message_ptr {
        return message_ptr(new message(sender_, std::forward<T>(name), std::move(detail::any(std::tuple<type_traits::decay_t<Args>...>{std::forward<Args>(args)...}))));
    }

} // namespace actor_zeta