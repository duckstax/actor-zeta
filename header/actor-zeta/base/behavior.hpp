#pragma once

#include <actor-zeta/mailbox/id.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/mailbox/id.hpp>
#include <actor-zeta/mailbox/message.hpp>

namespace actor_zeta { namespace base {

    void error_skip(const std::string& sender, const std::string& reciever, mailbox::message_id handler);
    void error_skip(const std::string& reciever, mailbox::message_id handler);

    struct keep_behavior_t final {
        constexpr keep_behavior_t() noexcept {}
    };

    constexpr keep_behavior_t skip_behavior = keep_behavior_t{};

    class behavior_t final {
    public:
        using id = mailbox::message_id;

        behavior_t() = delete;
        behavior_t(const behavior_t&) = delete;
        behavior_t&operator=(const behavior_t&) = delete;

        behavior_t( behavior_t&&) = default;
        behavior_t&operator=(behavior_t&&) = default;

        explicit behavior_t(actor_zeta::pmr::memory_resource* resource) {

        }

        behavior_t(actor_zeta::pmr::memory_resource* resource,id name, action handler) {
            ///assert(id_.integer_value() == mailbox::detail::default_async_value);
            id_ = name;
            handler_ = std::move(handler);
        }

        explicit operator bool() {
            return bool(handler_);
        }

        void operator()(mailbox::message* msg) {
            ///assert(msg->command() == id_);
            handler_(msg);
        }

        void assign(id name, action handler) {
            id_ = name;
            handler_ = std::move(handler);
        }

    private:
        id id_{mailbox::detail::default_async_value};
        action handler_;
    };

    template<class Key,class Value>
    behavior_t& behavior(behavior_t& instance, Key key, Value&& f) {
        instance.assign(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(std::forward<Value>(f)));
        return instance;
    }

    template<class Value>
    behavior_t& behavior(behavior_t& instance, mailbox::message_id key, Value&& f) {
        instance.assign(key, make_handler(std::forward<Value>(f)));
        return instance;
    }


    template<class Key,class Actor, typename F>
    behavior_t& behavior(behavior_t& instance, Key key, Actor* ptr, F&& f) {
        auto id =static_cast<uint64_t>(key);
        instance.assign(mailbox::make_message_id(id), make_handler(ptr,std::forward<F>(f)));
        return instance;
    }

    template<class F>
    behavior_t& behavior(behavior_t& instance, F&& f) {
        instance.assign(mailbox::message_id{},std::move(action(std::forward<F>(f))));
        return instance;
    }
//// todo: rename behavior
    template<class F>
    behavior_t behavior(actor_zeta::pmr::memory_resource*resource, F&& f) {
        return {resource,mailbox::message_id{}, std::move(action(std::forward<F>(f)))};
    }
/*
    template<class Actor, typename Value>
    behavior_t behavior(actor_zeta::pmr::memory_resource*resource, Actor* ptr, Value&& f) {
        return {resource,mailbox::message_id{}, ptr,std::forward<Value>(f)};
    }
*/
    template<class T>
    void invoke(behavior_t& instance,T* ptr, mailbox::message* msg) {
        instance(msg);
        /// todo: add error handling
        /*
        auto reciever = ptr->type();
        if (msg->sender()) {
            auto sender = msg->sender()->type();
            error_skip(sender, reciever, msg->command());
        } else {
            error_skip(reciever, msg->command());
        }
         */
    }

}} // namespace actor_zeta::base