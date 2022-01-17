#pragma once

#include <set>
#include <unordered_map>

#include "actor-zeta/forwards.hpp"
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/message.hpp>

namespace actor_zeta { namespace base {

    void error_skip(detail::string_view sender, detail::string_view reciever, detail::string_view handler) ;

    class intrusive_behavior_t   {
    protected:
        template<class T>
        void execute(T* ptr, message* msg) {
            auto it = handlers_.find(msg->command());
            if (it != handlers_.end()) {
                return it->second(msg);
            }
            auto sender = msg->sender().type();
            auto reciever = ptr->type();
            error_skip(sender, reciever, msg->command());
        }

        template<class F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        template<class Actor,typename F>
        auto add_handler(detail::string_view name,Actor*ptr, F&& f) -> void{
            on(name, make_handler(std::forward<F>(f), ptr));
        }

        auto message_types() const -> std::set<std::string>;

    private:
        using key_type = detail::string_view;
        using value_type = action;
        using handler_storage_t = std::unordered_map<key_type, value_type>;

        bool on(key_type name, value_type handler);
        handler_storage_t handlers_;
    };

}} // namespace actor_zeta::base