#include <iostream>

// clang-format off
#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/handler.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/impl/handler.ipp>
#include <actor-zeta/actor/communication_module.hpp>
// clang-format on

namespace actor_zeta { namespace actor {

        inline void error_sync_contacts(detail::string_view __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        void communication_module::enqueue(messaging::message msg) {
            enqueue(std::move(msg), nullptr);
        }

        auto  communication_module::message_types() const -> std::set<std::string> {
            std::set<std::string> types;

            for(const auto&i: dispatch()) {
                types.emplace(std::to_string(i.first));
            }

            return types;
        }

        auto communication_module::all_view_address() const -> void  {
            for (auto &i: *contacts_)
                std::cerr << i.first << std::endl;
        }

        auto communication_module::addresses(detail::string_view name) -> actor_address& {
            return contacts_->at(name);
        }

        auto communication_module::self()  -> actor_address  {
            return address();
        }

        auto communication_module::dispatch() -> dispatcher_t & {
            return dispatcher_;
        }

        auto communication_module::dispatch() const -> const dispatcher_t & {
            return dispatcher_;
        }

        auto communication_module::type() const -> abstract {
            return type_.type;
        }

        auto communication_module::name() const -> detail::string_view {
            return type_.name;
        }

        communication_module::~communication_module() {}

        communication_module::communication_module(detail::string_view name, abstract type)
            : contacts_(new std::unordered_map<detail::string_view,actor_address>)
            , type_{0,type,name}
            {
            initialize();
        }

        actor_address communication_module::address() const noexcept {
            return actor_address{const_cast<communication_module*>(this)};
        }

        void communication_module::initialize() {
            add_handler(
                    "sync_contacts",
                    bind(&communication_module::add_link,this)
            );

            add_handler(
                    "add_link",
                    bind(&communication_module::add_link,this)
            );

            ///add_handler(
            ///        "remove_link",
            ///        bind(&communication_module::remove_link,this)
            //);
        }

        void communication_module::add_link(actor_address address) {

            if (address) {
                auto name = address->name();
                contacts_->emplace(name, std::move(address));
            } else {
                error_sync_contacts(address->name());
            }

        }

        void communication_module::remove_link(const actor_address& address) {
            auto it = contacts_->find(address->name());
            if(it != contacts_->end()){
                contacts_->erase(it);
            }
        }

        void communication_module::remove_link(detail::string_view name) {
            auto it = contacts_->find(name);
            if(it != contacts_->end()){
                contacts_->erase(it);
            }
        }

        auto communication_module::broadcast(messaging::message msg) -> bool {

            auto tmp = std::move(msg);

            for(auto&i:*contacts_){
                i.second->enqueue(tmp.clone());
            }

            return true;
        }

        auto communication_module::add_handler(detail::string_view name, handler *handler_ptr) -> void {
            dispatch().on(name, handler_ptr);
        }

    }}