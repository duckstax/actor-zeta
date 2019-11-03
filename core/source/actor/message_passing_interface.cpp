#include <iostream>

#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/impl/handler.ipp>
#include <actor-zeta/actor/message_passing_interface.hpp>

namespace actor_zeta { namespace actor {

        inline void error_sync_contacts(detail::string_view __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

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
            for (auto &i: *contacts_)
                std::cerr << i.first << std::endl;
        }

        auto message_passing_interface::addresses(detail::string_view name) -> actor_address& {
            return contacts_->at(name);
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

        message_passing_interface::message_passing_interface(detail::string_view name,abstract type)
            : contacts_(new std::unordered_map<detail::string_view,actor_address>)
            , type_{0,type,name}
            {
            initialize();
        }

        actor_address message_passing_interface::address() const noexcept {
            return actor_address{const_cast<message_passing_interface*>(this)};
        }

        void message_passing_interface::initialize() {
            add_handler(
                    "sync_contacts",
                    [this](context &context_) {
                        auto address = context_.current_message().body<actor_address>();
                        add_link(std::move(address));
                    }
            );

            add_handler(
                    "add_link",
                    [this](context &context_) {
                        auto address = context_.current_message().body<actor_address>();
                        add_link(std::move(address));
                    }
            );

            add_handler(
                    "remove_link",
                    [this](context &context_) {
                        auto address = context_.current_message().body<actor_address>();
                        remove_link(address);
                    }
            );
        }

        void message_passing_interface::add_link(actor_address address) {

            if (address) {
                auto name = address->name();
                contacts_->emplace(name, std::move(address));
            } else {
                error_sync_contacts(address->name());
            }

        }

        void message_passing_interface::remove_link(const actor_address& address) {
            auto it = contacts_->find(address->name());
            if(it != contacts_->end()){
                contacts_->erase(it);
            }
        }

        void message_passing_interface::remove_link(detail::string_view name) {
            auto it = contacts_->find(name);
            if(it != contacts_->end()){
                contacts_->erase(it);
            }
        }

        auto message_passing_interface::broadcast(messaging::message msg) -> bool {

            auto tmp = std::move(msg);

            for(auto&i:*contacts_){
                i.second->enqueue(tmp.clone());
            }

            return true;
        }

    }}