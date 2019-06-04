#include <utility>
#include <iostream>

#include <actor-zeta/actor/local_actor.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/environment/environment.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/channel/channel.hpp>
#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace actor {

        inline void error_sync_contacts(const std::string &__error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        inline void error_skip(detail::string_view  __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Skip" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        inline void error_add_channel(const std::string &__error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization channel type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        local_actor::local_actor(
                environment::abstract_environment *env,
                const std::string &type
        ) :
                abstract_actor(env, type){
            initialize();
            type_.location = locations::local;
        }

        void local_actor::initialize() {
            add_handler(
                    "sync_contacts",
                    [](context &context_) {
                        auto address = context_.message().body<actor_address>();

                        if (address) {
                            context_->addresses(address);
                        } else {
                            error_sync_contacts(address->name());
                        }
                    }
            );

            // TODO: "skip" -> "" ?
            add_handler(
                    "skip",
                    [](context &context_) {
                        error_skip(context_.message().command()/*.to_string()*/);
                    }
            );

            add_handler(
                    "add_channel",
                    [](context &context_) {
                        auto channel_ = context_.message().body<channel::channel>();
                        if (channel_) {
                            context_->channel(channel_);
                        } else {
                            error_add_channel(channel_->name());
                        }
                    }
            );

        }

        auto local_actor::all_view_address() const -> void  {
          for (auto &i: contacts)
              std::cout << i.first << std::endl;
        }

        local_actor::~local_actor() {

        }

        executor::execution_device *local_actor::attach() const {
            return executor_;
        }

        void local_actor::attach(executor::execution_device *e) {
            if (e!= nullptr) {
                executor_ = e;
            }
        }

        void local_actor::addresses(actor_address aa) {
            contacts.emplace(aa->name(), aa);
        }

        void local_actor::channel(channel::channel channel_) {
            channels.emplace(channel_->name(),channel_);
        }

        auto local_actor::addresses(const std::string &name) -> actor_address& {
            return contacts.at(name);
        }

        auto local_actor::channel(const std::string &name) -> channel::channel& {
            return channels.at(name);
        }

        std::set<std::string> local_actor::message_types() const {
            std::set<std::string> types;

            for(const auto&i: dispatch()) {
                types.emplace(std::to_string(i.first));
            }

            return types;
        }

        auto local_actor::self()  -> actor_address  {
            return address();
        }

    }
}