#pragma once

#include <set>
#include <unordered_map>
#include <unordered_set>

#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/mailbox/id.hpp>

namespace actor_zeta { namespace base {

    void error_skip(detail::string_view sender, detail::string_view reciever, mailbox::message_id handler) ;

    class intrusive_behavior_t   {
    protected:
        using key_type = mailbox::message_id;
        using value_type = action;

        template<class T>
        void execute(T* ptr, mailbox::message* msg) {
            auto id = msg->command();
            auto it = handlers_.find(msg->command());
            if (it != handlers_.end()) {
                return it->second(msg);
            }
            auto sender = msg->sender()->type();
            auto reciever = ptr->type();
            error_skip(sender, reciever, msg->command());
        }

        template<class Key, class Value>
        auto add_handler(Key key, Value&& f) -> typename std::enable_if<!std::is_member_function_pointer<Value>::value>::type {
            on(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(std::forward<Value>(f)));
        }

        template<class Key, class Value>
        auto add_handler(Key key, Value&& f) -> typename std::enable_if<std::is_member_function_pointer<Value>::value>::type {
            on(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(std::forward<Value>(f), static_cast<typename type_traits::get_callable_trait_t<Value>::class_type*>(this)));
        }

        template<class Key, class Actor, typename F>
        auto add_handler(Key key, Actor* ptr, F&& f) -> void {
            on(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(std::forward<F>(f), ptr));
        }

        auto message_types() const -> std::unordered_set<key_type>;

    private:
        using handler_storage_t = std::unordered_map<key_type, value_type>;
        bool on(key_type name, value_type handler);
        handler_storage_t handlers_;
    };

}} // namespace actor_zeta::base