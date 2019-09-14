#include <actor-zeta/actor/base_actor.hpp>
#include <iostream>

namespace actor_zeta { namespace actor {

        inline void error_sync_contacts(detail::string_view __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        void base_actor::initialize() {
            add_handler(
                    "sync_contacts",
                    [this](context &context_) {
                        auto address = context_.message().body<actor_address>();
                        add_link(std::move(address));
                    }
            );

            add_handler(
                    "add_link",
                    [this](context &context_) {
                        auto address = context_.message().body<actor_address>();
                        add_link(std::move(address));
                    }
            );

            add_handler(
                    "remove_link",
                    [this](context &context_) {
                        auto address = context_.message().body<actor_address>();
                        remove_link(address);
                    }
            );
        }

        void base_actor::add_link(actor_address address) {

            if (address) {
                auto name = address->name();
                contacts.emplace(name,std::move(address));
            } else {
                error_sync_contacts(address->name());
            }

        }

        void base_actor::remove_link(const actor_address& address) {
            auto it = contacts.find(address->name());
            if(it != contacts.end()){
                contacts.erase(it);
            }
        }

        void base_actor::remove_link(detail::string_view name) {
            auto it = contacts.find(name);
            if(it != contacts.end()){
                contacts.erase(it);
            }
        }

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
            initialize();
        }

        base_actor::~base_actor() {}
    }}