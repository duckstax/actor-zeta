#pragma once

// clang-format off
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/type_traits.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
// clang-format on

namespace actor_zeta {

    template<class T>
    auto make_message_ptr(base::address_t sender_, T name) -> base::message* {
        return new base::message(std::move(sender_), std::forward<T>(name));
    }

    template<class T, typename Arg>
    auto make_message_ptr(base::address_t sender_, T name, Arg&& arg) -> base::message* {
        return new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<class T, typename... Args>
    auto make_message_ptr(base::address_t sender_, T name, Args&&... args) -> base::message* {
        return new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<Args>(args)...)));
    }

    template<class T>
    auto make_message(base::address_t sender_, T name) -> base::message_ptr {
        return base::message_ptr(new base::message(std::move(sender_), std::forward<T>(name)));
    }

    template<class T, typename Arg>
    auto make_message(base::address_t sender_, T name, Arg&& arg) -> base::message_ptr {
        return base::message_ptr(new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg)))));
    }

    template<class T, typename... Args>
    auto make_message(base::address_t sender_, T name, Args&&... args) -> base::message_ptr {
        return base::message_ptr(new base::message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<Args>(args)...))));
    }

} // namespace actor_zeta
