#include <iostream>

#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message_header.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/message_passing_interface.hpp>
#include <actor-zeta/actor/handler.hpp>

namespace actor_zeta { namespace actor {

        void message_passing_interface::enqueue(messaging::message msg) {
            enqueue(std::move(msg), nullptr);
        }

        auto  message_passing_interface::message_types() const -> std::set<std::string> {
            std::set<std::string> types;

            for(const auto&i: dispatch()) {
                types.emplace(std::to_string(i.first));
            }

            return types;
        }

        auto message_passing_interface::all_view_address() const -> void  {
            for (auto &i: contacts)
                std::cerr << i.first << std::endl;
        }

        auto message_passing_interface::addresses(detail::string_view name) -> actor_address& {
            return contacts.at(name);
        }

        auto message_passing_interface::self()  -> actor_address  {
            return address();
        }

        auto message_passing_interface::dispatch() -> dispatcher_t & {
            return dispatcher_;
        }

        auto message_passing_interface::dispatch() const -> const dispatcher_t & {
            return dispatcher_;
        }

        auto message_passing_interface::type() const -> abstract {
            return type_.type;
        }

        auto message_passing_interface::name() const -> detail::string_view {
            return type_.name;
        }

        message_passing_interface::~message_passing_interface() {}

        message_passing_interface::message_passing_interface(detail::string_view name,abstract type) {
            type_.name = name;
            type_.type = type;
        }

        actor_address message_passing_interface::address() const noexcept {
            return actor_address{const_cast<message_passing_interface*>(this)};
        }

    }}