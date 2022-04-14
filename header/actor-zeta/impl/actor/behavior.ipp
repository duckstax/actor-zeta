#pragma once

#include <actor-zeta/base/behavior.hpp>

#include <iostream>

namespace actor_zeta { namespace base {

    void error_duplicate_handler(mailbox::message_id error) {
        std::cerr << "Duplicate" << '\n';
        std::cerr << "Handler: " << error.integer_value() << '\n';
        std::cerr << "Duplicate" << std::endl;
    }

    void error_add_handler(mailbox::message_id error) {
        std::cerr << "error add handler" << '\n';
        std::cerr << "Handler: " << error.integer_value() << '\n';
        std::cerr << "error add handler" << std::endl;
    }

    void error_skip(const std::string& sender, const std::string& reciever, mailbox::message_id handler) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Skip, can't find handler: " << reciever << "::" << handler.integer_value();
        std::cerr << " sender: " << sender << "\n";
        std::cerr << "WARNING" << std::endl;
    }


    void error_skip(const std::string& reciever, mailbox::message_id handler) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Skip, can't find handler: " << reciever << "::" << handler.integer_value();
        std::cerr << " sender: " << "Not Sender" << "\n";
        std::cerr << "WARNING" << std::endl;
    }

    bool intrusive_behavior_t::on(key_type name, value_type handler) {
        auto it = handlers_.find(name);
        bool status = false;
        if (it == handlers_.end()) {
            auto it1 = handlers_.emplace(name, std::move(handler));
            status = it1.second;
            if (status == false) {
                error_add_handler(name);
            }
        } else {
            error_duplicate_handler(name);
        }

        return status;
    }

    auto intrusive_behavior_t::message_types() const -> std::set<mailbox::message_id> {
        std::set<mailbox::message_id> types;
        for (const auto& i : handlers_) {
            types.emplace(i.first);
        }
        return types;
    }

}} // namespace actor_zeta::base