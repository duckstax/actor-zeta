#include <iostream>

// clang-format off
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address_type.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/impl/handler.ipp>
#include <actor-zeta/base/communication_module.hpp>
// clang-format on

namespace actor_zeta { namespace base {

        inline void error_sync_contacts(detail::string_view __error__) {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization address_type type:" << __error__ << std::endl;
            std::cerr << "WARNING" << std::endl;
        }

        void communication_module::enqueue(messaging::message msg) {
            enqueue(std::move(msg), nullptr);
        }

        auto  communication_module::message_types() const -> std::set<std::string> {
            std::set<std::string> types;

            for(const auto&i: dispatch()) {
                types.emplace(std::string(i.first.begin(), i.first.end()));
            }

            return types;
        }

        auto communication_module::all_view_address() const -> void  {
            for (auto &i: *contacts_)
                std::cerr << i.first << std::endl;
        }

        auto communication_module::addresses(detail::string_view name) -> address_type& {
            return contacts_->at(name);
        }

        auto communication_module::self()  -> address_type {
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
            : contacts_(new std::unordered_map<detail::string_view, address>)
            , type_{0,type,name}
            {
            initialize();
        }

        address_type communication_module::address() const noexcept {
            return address_type{const_cast<communication_module*>(this)};
        }

        void communication_module::initialize() {
            add_handler(
                    "add_link",
                    &communication_module::add_link
            );

            add_handler(
                    "remove_link",
                    &communication_module::remove_link
            );
        }

        void communication_module::add_link(address_type address) {

            if (address) {
                auto name = address->name();
                contacts_->emplace(name, std::move(address));
            } else {
                error_sync_contacts(address->name());
            }

        }

        void communication_module::remove_link(const address_type& address) {
            auto it = contacts_->find(address->name());
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
        void communication_module::enqueue(messaging::message msg, executor::execution_device* ptr) {
            enqueue_base(std::move(msg),ptr);
        }

}}