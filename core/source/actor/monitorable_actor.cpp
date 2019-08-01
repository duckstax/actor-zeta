#include <utility>
#include <iostream>

#include <actor-zeta/actor/monitorable_actor.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace actor {

        inline void error_sync_contacts(detail::string_view __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        inline void error_skip(detail::string_view  __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Skip" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        monitorable_actor::monitorable_actor(
                supervisor *env,
                detail::string_view name
        )
        : base_actor(name)
        , supervisor_(env){
            initialize();
            type_.type = abstract::actor;
        }

        void monitorable_actor::initialize() {
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

            // TODO: "skip" -> "" ?
            add_handler(
                    "skip",
                    [](context &context_) {
                        error_skip(context_.message().command()/*.to_string()*/);
                    }
            );
        }

        monitorable_actor::~monitorable_actor() {

        }

        executor::execution_device *monitorable_actor::attach() const {
            return executor_;
        }

        void monitorable_actor::attach(executor::execution_device *e) {
            if (e!= nullptr) {
                executor_ = e;
            }
        }

        auto monitorable_actor::env() -> supervisor * {
            return supervisor_;
        }

        void monitorable_actor::add_link(actor_address address) {

            if (address) {
                auto name = address->name();
                contacts.emplace(name,std::move(address));
            } else {
                error_sync_contacts(address->name());
            }

        }

        void monitorable_actor::remove_link(const actor_address& address) {
            auto it = contacts.find(address->name());
            if(it != contacts.end()){
                contacts.erase(it);
            }
        }

        void monitorable_actor::remove_link(detail::string_view name) {
            auto it = contacts.find(name);
            if(it != contacts.end()){
                contacts.erase(it);
            }
        }
    }}