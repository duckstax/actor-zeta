#pragma once
#include <iostream>
#include <set>
#include <unordered_map>

#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/string_view.hpp>

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
    /*
    class behavior_base {
    public:
        void execute(actor_abstract* ptr, message& msg) {
            execute_impl(ptr, msg);
        }

    protected:
        virtual void execute_impl(actor_abstract* ptr, message& msg) = 0;
        virtual ~behavior_base() = default;
    };

    class behavior_empty_t final : public behavior_base {
    public:
        void execute_impl(actor_abstract* ptr, message& msg) {
            assert(true);
        }
    };
    */
    class behavior_t final /* : public behavior_base*/ {
    public:
        using key_type = detail::string_view;
        using value_type = detail::unique_function<void(communication_module*)>;
        using handler_storage_t = std::unordered_map<key_type, value_type>;

        behavior_t() = default;

        template<class F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        auto message_types() const -> std::set<std::string> {
            std::set<std::string> types;
            for (const auto& i : handlers_) {
                types.emplace(std::string(i.first.begin(), i.first.end()));
            }
            return types;
        }

        void execute(actor_abstract* ptr, message& msg) {
            auto it = handlers_.find(msg.command());
            if (it != handlers_.end()) {
                return it->second(ptr);
            } else {
                /*
                    auto sender = ptr->sender().type();
                    auto reciever = ptr->type();
                    error_skip(sender, reciever, msg.command());
                     */
            }
        }

    private:
        bool on(detail::string_view name, value_type handler) {
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

        handler_storage_t handlers_;
    };

}} // namespace actor_zeta::base