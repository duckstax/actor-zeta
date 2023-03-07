#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/mailbox/id.hpp>

namespace actor_zeta { namespace base {

    /**
     * @brief
     *
     * @param sender
     * @param reciever
     * @param handler
     */
    inline void error_skip(const char* sender, const char* reciever, mailbox::message_id handler) {
        fprintf(stderr,
            "WARNING >>>\nSkip, can't find handler: '%s' :: %llu\nsender: '%s'\nWARNING <<<\n",
            reciever, handler.integer_value(), sender);
    }
    /**
     * @brief
     *
     * @param reciever
     * @param handler
     */
    inline void error_skip(const char* reciever, mailbox::message_id handler) {
        fprintf(stderr,
            "WARNING >>>\nSkip, can't find handler: '%s' :: %llu\nsender: no-sender\nWARNING <<<\n",
            reciever, handler.integer_value());
    }

    /**
     * @class intrusive_behavior_t
     * @brief
     *
     * @tparam actor_traits
     */
    template<typename actor_traits>
    class intrusive_behavior_t {
        using memory_resource_ptr = typename actor_traits::memory_resource_ptr;

        memory_resource_ptr memory_resource_ = nullptr;

    protected:
        using key_type = mailbox::message_id;
        using value_type = action;

        inline auto resource() const -> memory_resource_ptr {
            return memory_resource_;
        }

        intrusive_behavior_t(memory_resource_ptr mr)
            : memory_resource_(mr ? mr : actor_zeta::detail::pmr::get_default_resource()) { assert(resource()); }
        virtual ~intrusive_behavior_t() = default;

        intrusive_behavior_t(intrusive_behavior_t&&) = default;
        intrusive_behavior_t(intrusive_behavior_t&) = default;
        intrusive_behavior_t(const intrusive_behavior_t&) = default;

        intrusive_behavior_t& operator=(intrusive_behavior_t&&) = default;
        intrusive_behavior_t& operator=(intrusive_behavior_t&) = default;
        intrusive_behavior_t& operator=(const intrusive_behavior_t&) = default;

        template<class T>
        void execute(T* ptr, mailbox::message* msg) {
            auto id = msg->command();
            auto it = handlers_.find(msg->command());
            if (it != handlers_.end()) {
                return it->second(msg);
            }

            auto reciever = ptr->type();
            if( msg->sender()){
                auto sender = msg->sender()->type();
                error_skip(sender, reciever, msg->command());
            } else {
                error_skip(reciever, msg->command());
            }

        }

        template<class Key, class Value>
        auto add_handler(Key key, Value&& f) -> typename std::enable_if<!std::is_member_function_pointer<Value>::value>::type {
            auto id = mailbox::make_message_id(static_cast<uint64_t>(key));
            on(id, make_handler(resource(), std::forward<Value>(f)));
        }

        template<class Key, class Value>
        auto add_handler(Key key, Value&& f) -> typename std::enable_if<std::is_member_function_pointer<Value>::value>::type {
            on(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(resource(), std::forward<Value>(f), static_cast<typename type_traits::get_callable_trait_t<Value>::class_type*>(this)));
        }

        template<class Key, class Actor, typename F>
        auto add_handler(Key key, Actor* ptr, F&& f) -> void {
            on(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(resource(), std::forward<F>(f), ptr));
        }

        template<class Value>
        auto add_handler(mailbox::message_id key, Value&& f) -> typename std::enable_if<!std::is_member_function_pointer<Value>::value>::type {
            on(key, make_handler(resource(), std::forward<Value>(f)));
        }

        template<class Value>
        auto add_handler(mailbox::message_id key, Value&& f) -> typename std::enable_if<std::is_member_function_pointer<Value>::value>::type {
            on(key, make_handler(resource(), std::forward<Value>(f), static_cast<typename type_traits::get_callable_trait_t<Value>::class_type*>(this)));
        }

        template<class Actor, typename F>
        auto add_handler(mailbox::message_id key, Actor* ptr, F&& f) -> void {
            on(key, make_handler(resource(), std::forward<F>(f), ptr));
        }

        auto message_types() const -> typename actor_traits::template set_type<key_type>;

    private:
        using handler_storage_t = typename actor_traits::template unordered_map_type<key_type, value_type>;
        bool on(key_type name, value_type handler);
        handler_storage_t handlers_;
    };

    inline void error_duplicate_handler(mailbox::message_id error) {
        fprintf(stderr,
            "Duplicate\nHandler: %llu\nDuplicate\n", error.integer_value());
    }

    inline void error_add_handler(mailbox::message_id error) {
        fprintf(stderr,
            "Error add handler\nHandler: %llu\nError add handler\n", error.integer_value());
    }

    template<typename actor_traits>
    bool intrusive_behavior_t<actor_traits>::on(key_type name, value_type handler) {
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

    template<typename actor_traits>
    auto intrusive_behavior_t<actor_traits>::message_types() const -> typename actor_traits::template set_type<key_type> {
        typename actor_traits::template set_type<key_type> types{resource()};
        for (const auto& i : handlers_) {
            types.emplace(i.first);
        }
        return types;
    }

}} // namespace actor_zeta::base