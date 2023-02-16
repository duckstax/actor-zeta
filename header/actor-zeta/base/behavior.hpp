#pragma once

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

    constexpr keep_behavior_t keep_behavior = keep_behavior_t{};

    class behavior_t final {
    public:
        using id = mailbox::message_id;

        behavior_t() = default;

        explicit behavior_t(actor_zeta::detail::pmr::memory_resource* resource) {

        }

        explicit operator bool() {
            return bool(handler_);
        }

        void operator()(mailbox::message* msg) {
            assert(msg->command() == id_);
            handler_(msg);
        }

        void assign(id name, action handler) {
            id_ = name;
            handler_ = std::move(handler);
        }

    private:
        id id_;
        action handler_;
    };

    template<class Key,class Value>
    behavior_t& behavior(behavior_t& instance, Key key, Value&& f) {
        instance.assign(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(std::forward<Value>(f)));
        return instance;
    }

    template<class Key,class Actor, typename F>
    behavior_t& behavior(behavior_t& instance, Key key, Actor* ptr, F&& f) {
        instance.assign(mailbox::make_message_id(static_cast<uint64_t>(key)), make_handler(ptr,std::forward<F>(f)));
        return instance;
    }

    template<class Value>
    behavior_t& behavior(behavior_t& instance, Value&& f) {
        instance.assign(mailbox::message_id{}, make_handler(std::forward<Value>(f)));
        return instance;
    }

    template<class Value>
    behavior_t behavior(actor_zeta::detail::pmr::memory_resource*resource, Value&& f) {
        behavior_t instance(resource);
        instance.assign(mailbox::message_id{}, make_handler(std::forward<Value>(f)));
        return instance;
    }

    template<class Actor, typename F>
    behavior_t behavior(actor_zeta::detail::pmr::memory_resource*resource, Actor* ptr, F&& f) {
        behavior_t instance(resource);
        instance.assign(mailbox::message_id{}, make_handler(ptr,std::forward<F>(f)));
        return instance;
    }

    template<class T>
    void invoke(behavior_t& instance,T* ptr, mailbox::message* msg) {
        instance(msg);
        auto reciever = ptr->type();
        if (msg->sender()) {
            auto sender = msg->sender()->type();
            error_skip(sender, reciever, msg->command());
        } else {
            error_skip(reciever, msg->command());
        }
    }

}} // namespace actor_zeta::base