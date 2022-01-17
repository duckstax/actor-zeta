#pragma once

#include <actor-zeta/base/behavior.hpp>

#include <iostream>
#include <set>
#include <unordered_map>

namespace actor_zeta { namespace base {

    void error_duplicate_handler(detail::string_view error) {
        std::cerr << "Duplicate" << '\n';
        std::cerr << "Handler: " << error << '\n';
        std::cerr << "Duplicate" << std::endl;
    }

    void error_add_handler(detail::string_view error) {
        std::cerr << "error add handler" << '\n';
        std::cerr << "Handler: " << error << '\n';
        std::cerr << "error add handler" << std::endl;
    }

    void error_skip(detail::string_view sender, detail::string_view reciever, detail::string_view handler) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Skip, can't find handler: " << reciever << "::" << handler;
        std::cerr << " sender: " << sender << "\n";
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

    auto intrusive_behavior_t::message_types() const -> std::set<std::string> {
        std::set<std::string> types;
        for (const auto& i : handlers_) {
            types.emplace(std::string(i.first.begin(), i.first.end()));
        }
        return types;
    }

}} // namespace actor_zeta::base