#include <iostream>

// clang-format off
#include <handler.hpp>
#include <address_t.hpp>
#include <message.hpp>
#include <actor-zeta/impl/handler.ipp>
#include <communication_module.hpp>
// clang-format on

#include <actor-zeta/abstract_actor.hpp>
#include <actor-zeta/abstract_supervisor.hpp>

namespace actor_zeta {

    inline void error_sync_contacts(detail::string_view error) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Not initialization address_type type:" << error << std::endl;
        std::cerr << "WARNING" << std::endl;
    }


    auto communication_module::message_types() const -> std::set<std::string> {
        std::set<std::string> types;

        for (const auto& i : dispatch()) {
            types.emplace(std::string(i.first.begin(), i.first.end()));
        }

        return types;
    }

    auto communication_module::all_view_address() const -> void {
        for (auto& i : *contacts_) {
            std::cerr << i.first << std::endl;
        }
    }

    auto communication_module::addresses(detail::string_view name) -> address_t& {
        return contacts_->at(name);
    }

    auto communication_module::self() -> address_t {
        return this->address();
    }

    auto communication_module::type() const -> abstract {
        return type_;
    }

    communication_module::~communication_module() = default;

    communication_module::communication_module(detail::string_view name, abstract type)
        : contacts_(new std::unordered_map<detail::string_view, address_t>)
        , id_(0)
        , type_(type)
        , name_(name) {
        initialize();
    }

    void communication_module::initialize() {
        add_handler(
            "add_link",
            &communication_module::add_link);

        add_handler(
            "remove_link",
            &communication_module::remove_link);
    }

    void communication_module::add_link(const address_t& address) {
        if (address) {
            auto name = address->name();
            contacts_->emplace(name, std::move(address));
        } else {
            error_sync_contacts(address->name());
        }
    }

    void communication_module::remove_link(const address_t& address) {
        auto it = contacts_->find(address->name());
        if (it != contacts_->end()) {
            contacts_->erase(it);
        }
    }

    auto communication_module::broadcast(message msg) -> bool {
        auto tmp = std::move(msg);

        for (auto& i : *contacts_) {
            enqueue_(i.second, tmp.clone());
        }

        return true;
    }

    auto communication_module::dispatch() -> dispatcher_t & {
        return dispatcher_;
    }

    auto communication_module::dispatch() const -> const dispatcher_t & {
        return dispatcher_;
    }



} // namespace actor_zeta