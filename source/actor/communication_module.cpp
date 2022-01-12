#include <iostream>

// clang-format off
#include <actor-zeta/context.hpp>
#include <actor-zeta/handler.hpp>
#include <actor-zeta/actor_address.hpp>
#include <actor-zeta/mail_box/message.hpp>
#include <actor-zeta/impl/handler.ipp>
#include <actor-zeta/communication_module.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    inline void error_sync_contacts(detail::string_view __error__) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    inline void error_duplicate_handler(detail::string_view _error_) {
        std::cerr << "Duplicate" << std::endl;
        std::cerr << "Handler: " << _error_ << std::endl;
        std::cerr << "Duplicate" << std::endl;
    }

    inline void error_add_handler(detail::string_view _error_) {
        std::cerr << "error add handler" << std::endl;
        std::cerr << "Handler: " << _error_ << std::endl;
        std::cerr << "error add handler" << std::endl;
    }

    inline void error_skip(detail::string_view __error__) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Skip : " << __error__ << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    void communication_module::execute(context& ctx) {
        auto it = handlers_.find(ctx.current_message()->command());
        if (it != handlers_.end()) {
            return it->second->invoke(ctx);
        } else {
            error_skip(ctx.current_message()->command());
        }
    }

    bool communication_module::on(detail::string_view name, handler* aa) {
        auto it = handlers_.find(name);
        bool status = false;
        if (it == handlers_.end()) {
            auto it1 = handlers_.emplace(name, std::unique_ptr<handler>(aa));
            status = it1.second;
            if (status == false) {
                error_add_handler(name);
            }
        } else {
            error_duplicate_handler(name);
        }

        return status;
    }

    void communication_module::enqueue(message_ptr msg) {
        enqueue(std::move(msg), nullptr);
    }

    auto communication_module::message_types() const -> std::set<std::string> {
        std::set<std::string> types;

        for (const auto& i : handlers_) {
            types.emplace(std::string(i.first.begin(), i.first.end()));
        }

        return types;
    }

    auto communication_module::all_view_address() const -> void {
        for (auto& i : *contacts_)
            std::cerr << i.first << std::endl;
    }

    auto communication_module::addresses(detail::string_view name) -> actor_address& {
        return contacts_->at(name);
    }

    auto communication_module::self() -> actor_address {
        return address();
    }

    auto communication_module::sub_type() const -> sub_type_t {
        return type_.sub_type_;
    }

    auto communication_module::type() const -> detail::string_view {
        return type_.type_;
    }

    communication_module::~communication_module() {}

    communication_module::communication_module(detail::string_view name, sub_type_t type)
        : contacts_(new std::unordered_map<detail::string_view, actor_address>)
        , type_{0, type, name} {
        initialize();
    }

    actor_address communication_module::address() const noexcept {
        return actor_address{const_cast<communication_module*>(this)};
    }

    void communication_module::initialize() {
        add_handler(
            "add_link",
            &communication_module::add_link);

        add_handler(
            "remove_link",
            &communication_module::remove_link);
    }

    void communication_module::add_link(actor_address address) {
        if (address) {
            auto name = address->type();
            contacts_->emplace(name, std::move(address));
        } else {
            error_sync_contacts(address->type());
        }
    }

    void communication_module::remove_link(const actor_address& address) {
        auto it = contacts_->find(address->type());
        if (it != contacts_->end()) {
            contacts_->erase(it);
        }
    }

    auto communication_module::broadcast(message_ptr msg) -> bool {
        auto tmp = std::move(msg);

        for (auto& i : *contacts_) {
            i.second->enqueue(message_ptr(tmp->clone()));
        }

        return true;
    }

    void communication_module::enqueue(message_ptr msg, executor::execution_device* e) {
        enqueue_base(std::move(msg), e);
    }

}} // namespace actor_zeta::base