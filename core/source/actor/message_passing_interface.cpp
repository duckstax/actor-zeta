#include <iostream>

// clang-format off
#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/impl/handler.ipp>
#include <actor-zeta/actor/abstract_async_container.hpp>
// clang-format on

namespace actor_zeta { namespace actor {

        inline void error_sync_contacts(detail::string_view __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        void abstract_async_container::enqueue(messaging::message msg) {
            enqueue(std::move(msg), nullptr);
        }

        auto  abstract_async_container::message_types() const -> std::set<std::string> {
            std::set<std::string> types;

            for(const auto&i: dispatch()) {
                types.emplace(std::to_string(i.first));
            }

            return types;
        }

        auto abstract_async_container::all_view_address() const -> void  {
            for (auto &i: *contacts_)
                std::cerr << i.first << std::endl;
        }

        auto abstract_async_container::addresses(detail::string_view name) -> actor_address& {
            return contacts_->at(name);
        }

        auto abstract_async_container::self()  -> actor_address  {
            return address();
        }

        auto abstract_async_container::dispatch() -> dispatcher_t & {
            return dispatcher_;
        }

        auto abstract_async_container::dispatch() const -> const dispatcher_t & {
            return dispatcher_;
        }

        auto abstract_async_container::type() const -> abstract {
            return type_.type;
        }

        auto abstract_async_container::name() const -> detail::string_view {
            return type_.name;
        }

        abstract_async_container::~abstract_async_container() {}

        abstract_async_container::abstract_async_container(detail::string_view name,abstract type)
            : contacts_(new std::unordered_map<detail::string_view,actor_address>)
            , type_{0,type,name}
            {
            initialize();
        }

        actor_address abstract_async_container::address() const noexcept {
            return actor_address{const_cast<abstract_async_container*>(this)};
        }

        void abstract_async_container::initialize() {
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

        void abstract_async_container::add_link(actor_address address) {

            if (address) {
                auto name = address->name();
                contacts_->emplace(name, std::move(address));
            } else {
                error_sync_contacts(address->name());
            }

        }

        void abstract_async_container::remove_link(const actor_address& address) {
            auto it = contacts_->find(address->name());
            if(it != contacts_->end()){
                contacts_->erase(it);
            }
        }

        void abstract_async_container::remove_link(detail::string_view name) {
            auto it = contacts_->find(name);
            if(it != contacts_->end()){
                contacts_->erase(it);
            }
        }

        auto abstract_async_container::broadcast(messaging::message msg) -> bool {

            auto tmp = std::move(msg);

            for(auto&i:*contacts_){
                i.second->enqueue(tmp.clone());
            }

            return true;
        }

    }}