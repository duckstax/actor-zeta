#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/type_traits.hpp>

#include "enums.hpp"
#include "counters.h"

template<class... Args>
struct counter_args_t {
    static constexpr size_t value = sizeof...(Args);
};

template<class Sup>
auto set_done(Sup* sup_ptr_)->void {
#ifdef BM_TRACE
    std::cout << std::this_thread::get_id() << " :: Going to sem done ... .. . " << reinterpret_cast<void*>(sup_ptr_) << std::endl;
#endif
    sup_ptr_->done();
}

class sup_iface;

class actor_t final : public actor_zeta::basic_async_actor {

    sup_iface* ptr_;

    std::map<name_t, actor_zeta::address_t> address_book_;

    template<size_t... I>
    auto perform(command_t cmd, actor_zeta::type_traits::index_sequence<I...>) -> void {
        actor_zeta::send(address_book_.begin()->second, address(), cmd, I...);
    }

public:
    auto add_address(actor_zeta::address_t address, name_t name) -> void {
        if (address && this != address.get()) {
            address_book_.emplace(name, std::move(address));
        }
    }

    template<class ...Args>
    auto start() -> void {
        perform(command_t::ping, actor_zeta::type_traits::make_index_sequence<counter_args_t<Args...>::value>());
    }

    template<class ...Args>
    auto ping(Args... args) -> void {
        counter_g++;
#ifdef BM_TRACE
        std::cout << std::this_thread::get_id() << " :: PING " << reinterpret_cast<void*>(this) << std::endl;
#endif
        perform(command_t::pong, actor_zeta::type_traits::make_index_sequence<counter_args_t<Args...>::value>());
    }

    template<class ...Args>
    auto pong(Args... args) -> void {
        counter_g++;
#ifdef BM_TRACE
        std::cout << std::this_thread::get_id() << " :: PONG " << reinterpret_cast<void*>(this) << std::endl;
#endif
        set_done(ptr_);
    }

    template<class Supervisor, class ...Args>
    actor_t(Supervisor* ptr, Args ...args)
        : actor_zeta::basic_async_actor(ptr, "Actor")
        , ptr_(static_cast<sup_iface*>(ptr))
    {
        add_handler(command_t::add_address, &actor_t::add_address);
        add_handler(command_t::start, &actor_t::start<Args...>);
        add_handler(command_t::ping, &actor_t::ping<Args...>);
        add_handler(command_t::pong, &actor_t::pong<Args...>);
    }

    auto make_type() const noexcept -> const char* const {
        return "actor";
    }

    /*actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case actor_zeta::make_message_id(command_t::add_address): {
                        add_address_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(command_t::start): {
                        start_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(command_t::ping): {
                        ping_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(command_t::pong): {
                        pong_(msg);
                        break;
                    }
                }
            });
    }*/
};
