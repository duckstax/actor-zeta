#include <iostream>

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/impl/handler.ipp>
#include <actor-zeta/base/communication_module.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    void error_sync_contacts(detail::string_view error) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Not initialization actor_address type:" << error << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    void error_duplicate_handler(detail::string_view error) {
        std::cerr << "Duplicate" << std::endl;
        std::cerr << "Handler: " << error << std::endl;
        std::cerr << "Duplicate" << std::endl;
    }

    void error_add_handler(detail::string_view error) {
        std::cerr << "error add handler" << std::endl;
        std::cerr << "Handler: " << error << std::endl;
        std::cerr << "error add handler" << std::endl;
    }

    void error_skip(detail::string_view sender,detail::string_view receiver,detail::string_view command) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Sender type: " << sender << std::endl;
        std::cerr << "Receiver type: " << receiver << std::endl;
        std::cerr << "Skip Command: " << command << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    void communication_module::execute() {
        auto it = handlers_.find(current_message()->command());
        if (it != handlers_.end()) {
            return it->second->invoke(this);
        } else {
            error_skip(current_message()->sender()->type(),type(),current_message()->command());
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

    auto communication_module::all_view_address() const -> std::vector<std::string> {
        std::vector<std::string> tmp ;
        tmp.reserve(contacts_->size());
        for (auto& i : *contacts_) {
            tmp.emplace_back(std::string(i.first.begin(), i.first.end()));
        }
        return tmp;
    }

    auto communication_module::addresses(detail::string_view name) -> actor_address& {
        return contacts_->at(name);
    }

    auto communication_module::self() -> actor_address {
        return address();
    }

    auto communication_module::sub_type() const -> sub_type_t {
        return sub_type_;
    }

    auto communication_module::type() const -> detail::string_view {
        return type_;
    }

    communication_module::~communication_module() {}

    communication_module::communication_module(detail::string_view name, sub_type_t type)
        : contacts_(new std::unordered_map<detail::string_view, actor_address>)
        , id_(0)
        , type_(name)
        , sub_type_(type) {
        initialize();
    }

    actor_address communication_module::address() const noexcept {
        return actor_address{const_cast<communication_module*>(this)};
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

    auto communication_module::current_message() -> message* {
        return current_message_impl();
    }

}} // namespace actor_zeta::base