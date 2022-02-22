#pragma once

// clang-format off
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/type_traits.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/rtt_message.hpp>
// clang-format on

namespace actor_zeta {

    template<class T>
    auto make_rtt_message_ptr(base::address_t sender_, T name) -> base::rtt_message* {
        return new base::rtt_message(std::move(sender_), std::forward<T>(name));
    }

    template<class T, typename Arg>
    auto make_rtt_message_ptr(base::address_t sender_, T name, Arg&& arg) -> base::rtt_message* {
        return new base::rtt_message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg))));
    }

    template<class T, typename... Args>
    auto make_rtt_message_ptr(base::address_t sender_, T name, Args&&... args) -> base::rtt_message* {
        return new base::rtt_message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<Args>(args)...)));
    }

    template<class T>
    auto make_rtt_message(base::address_t sender_, T name) -> base::rtt_message_ptr {
        return base::rtt_message_ptr(new base::rtt_message(std::move(sender_), std::forward<T>(name)));
    }

    template<class T, typename Arg>
    auto make_rtt_message(base::address_t sender_, T name, Arg&& arg) -> base::rtt_message_ptr {
        return base::rtt_message_ptr(new base::rtt_message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<type_traits::decay_t<Arg>>(arg)))));
    }

    template<class T, typename... Args>
    auto make_rtt_message(base::address_t sender_, T name, Args&&... args) -> base::rtt_message_ptr {
        return base::rtt_message_ptr(new base::rtt_message(std::move(sender_), std::forward<T>(name), std::move(detail::rtt(nullptr, std::forward<Args>(args)...))));
    }

} // namespace actor_zeta