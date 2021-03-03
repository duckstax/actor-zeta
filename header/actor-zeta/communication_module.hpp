#pragma once

#include <memory>
#include <set>
#include <unordered_map>
#include <iostream>

#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/forwards.hpp>
#include "message.hpp"

namespace actor_zeta {

    inline void error_skip(detail::string_view error) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Skip : " << error << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    inline void error_duplicate_handler(detail::string_view _error_) {
        std::cerr << "Duplicate" << std::endl;
        std::cerr << "Handler: " << _error_ << std::endl;
        std::cerr << "Duplicate" << std::endl;
    }

    inline void error_add_handler(detail::string_view error) {
        std::cerr << "error add handler" << std::endl;
        std::cerr << "Handler: " << error << std::endl;
        std::cerr << "error add handler" << std::endl;
    }

    using handler = std::function<void()>;

    class communication_module {
    public:
        communication_module();
        communication_module(const communication_module&) = delete;

        communication_module& operator=(const communication_module&) = delete;

        virtual ~communication_module();

        auto message_types() const -> std::set<std::string>;

    protected:
        using key_type = detail::string_view;
        using storage = std::unordered_map<key_type,handler>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;

        void execute( message msg) {
            auto it = handlers_.find(msg.command());
            if (it != handlers_.end()) {
                it->second();
            } else {
                error_skip(msg.command());
            }
        }

        template<class F>
        void on(detail::string_view name, F f) {
            auto it = handlers_.find(name);
            bool status = false;
            if (it == handlers_.end()) {
                auto it1 = handlers_.emplace(name, std::forward<F>(f));
                status = it1.second;
                if (status == false) {
                    error_add_handler(name);
                }
            } else {
                error_duplicate_handler(name);
            }
        }


        virtual auto current_message() -> message& =0;

        auto broadcast(message) -> bool;

        auto addresses(detail::string_view) -> address_t&;

        template<class F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        /**
           * debug method
           */
        auto all_view_address() const -> void;

        detail::string_view name_;

    private:
        void add_link(const address_t&);

        void remove_link(const address_t&);

        void initialize();
        using contacts_type = std::unordered_map<detail::string_view, address_t>;
        std::unique_ptr<contacts_type> contacts_;
        storage handlers_;
    };
} // namespace actor_zeta
