#include <actor-zeta/actor/base_actor.hpp>
#include <iostream>

namespace actor_zeta { namespace actor {

        auto base_actor::all_view_address() const -> void  {
            for (auto &i: contacts)
                std::cout << i.first << std::endl;
        }

        auto base_actor::addresses(detail::string_view name) -> actor_address& {
            return contacts.at(name);
        }

        std::set<std::string> base_actor::message_types() const {
            std::set<std::string> types;

            for(const auto&i: dispatch()) {
                types.emplace(std::to_string(i.first));
            }

            return types;
        }

        auto base_actor::self()  -> actor_address  {
            return address();
        }

        auto base_actor::dispatch() -> dispatcher_t & {
            return dispatcher_;
        }

        auto base_actor::dispatch() const -> const dispatcher_t & {
            return dispatcher_;
        }

        base_actor::base_actor(detail::string_view name) : abstract_actor(name) {

    }

        base_actor::~base_actor() {}
    }}