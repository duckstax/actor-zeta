#include <actor-zeta/actor/abstract_actor.hpp>

#include <iostream>

#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>


namespace actor_zeta { namespace actor {

        inline void error_sync_contacts(detail::string_view __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }


        abstract_actor::~abstract_actor() {

        }

        void abstract_actor::initialize() {
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

        void abstract_actor::add_link(actor_address address) {

            if (address) {
                auto name = address->name();
                contacts.emplace(name,std::move(address));
            } else {
                error_sync_contacts(address->name());
            }

        }

        void abstract_actor::remove_link(const actor_address& address) {
            auto it = contacts.find(address->name());
            if(it != contacts.end()){
                contacts.erase(it);
            }
        }

        void abstract_actor::remove_link(detail::string_view name) {
            auto it = contacts.find(name);
            if(it != contacts.end()){
                contacts.erase(it);
            }
        }

        abstract_actor::abstract_actor(detail::string_view name):message_passing_interface(name,abstract::actor) {
            initialize();
        }


}}
