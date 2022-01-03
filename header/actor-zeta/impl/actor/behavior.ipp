#pragma once

#include <actor-zeta/base/behavior.hpp>

#include <iostream>
#include <set>
#include <unordered_map>
/*
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/message.hpp>
*/
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

    auto behavior_container::assign(behavior_t& behavior) -> void {
        handlers_ = std::move(behavior.get());
    }

    auto behavior_container::message_types() const -> std::set<std::string> {
        std::set<std::string> types;
        for (const auto& i : handlers_->handlers_) {
            types.emplace(std::string(i.first.begin(), i.first.end()));
        }
        return types;
    }

    auto behavior_t::get() -> behavior_private_ptr {
        return std::move(handlers_);
    }

    auto behavior_t::message_types() const -> std::set<std::string> {
        std::set<std::string> types;
        for (const auto& i : handlers_->handlers_) {
            types.emplace(std::string(i.first.begin(), i.first.end()));
        }
        return types;
    }

    auto behavior_t::ptr() -> void* {
        return ptr_;
    }

    bool behavior_t::on(behavior_t::key_type name, behavior_t::value_type handler) {
        auto it = handlers_->handlers_.find(name);
        bool status = false;
        if (it == handlers_->handlers_.end()) {
            auto it1 = handlers_->handlers_.emplace(name, std::move(handler));
            status = it1.second;
            if (status == false) {
                error_add_handler(name);
            }
        } else {
            error_duplicate_handler(name);
        }

        return status;
    }

}} // namespace actor_zeta::base