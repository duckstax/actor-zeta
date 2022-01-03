#pragma once

#include <set>
#include <unordered_map>

#include "actor-zeta/base/forwards.hpp"
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/base/handler.hpp>

namespace actor_zeta { namespace base {

    void error_skip(detail::string_view sender, detail::string_view reciever, detail::string_view handler) ;

    struct behavior_private final {
        using key_type = detail::string_view;
        using value_type = detail::unique_function<void(communication_module*)>;
        using handler_storage_t = std::unordered_map<key_type, value_type>;
        handler_storage_t handlers_;
    };

    using behavior_private_ptr = std::unique_ptr<behavior_private>;

    class behavior_t;

    class behavior_container final {
    public:
        behavior_container() = default;
        auto assign(behavior_t& behavior) -> void;
        auto message_types() const -> std::set<std::string>;

        template<class T>
        void execute(T* ptr, message& msg) {
            auto it = handlers_->handlers_.find(msg.command());
            if (it != handlers_->handlers_.end()) {
                return it->second(ptr);
            }
            auto sender = msg.sender().type();
            auto reciever = ptr->type();
            error_skip(sender, reciever, msg.command());
        }

    private:
        behavior_private_ptr handlers_;
    };

    class behavior_t  {
    public:
        using value_type = behavior_private::value_type;
        using key_type = behavior_private::key_type;

        template<class Actor>
        behavior_t(Actor*ptr)
            : ptr_(ptr)
            , handlers_(new behavior_private){
        }

        auto get() -> behavior_private_ptr;
        bool on(key_type name, value_type handler);
        auto ptr() -> void*;
        auto message_types() const -> std::set<std::string>;

    private:
        void* ptr_;
        behavior_private_ptr handlers_;
    };

    template<class F>
    auto add_handler(behavior_t& behavior,behavior_t::key_type name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
        behavior.on(name, make_handler(std::forward<F>(f)));
    }

    template<typename F>
    auto add_handler(behavior_t& behavior,behavior_t::key_type name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
        behavior.on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(behavior.ptr())));
    }

    template<class Actor,typename F>
    auto add_handler(behavior_t& behavior,behavior_t::key_type name,Actor*ptr, F&& f) -> void{
        behavior.on(name, make_handler(std::forward<F>(f), ptr));
    }

}} // namespace actor_zeta::base