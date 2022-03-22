#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "forwards.hpp"
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

    class communication_module {
    public:
        using key_type = detail::string_view;
        using handler_storage_t = std::unordered_map<key_type, std::unique_ptr<handler>>;

        communication_module() = delete;
        communication_module(const communication_module&) = delete;
        communication_module& operator=(const communication_module&) = delete;
        virtual ~communication_module();

        auto type() const -> detail::string_view;
        auto id() const -> int64_t ;
        /**
        * debug method
        */
        auto message_types() const -> std::set<std::string>;
        auto enqueue(message_ptr) -> void;
        void enqueue(message_ptr, scheduler::execution_unit*);
        auto current_message() -> message*;

    protected:
        communication_module(std::string,int64_t);
        virtual auto current_message_impl() -> message* = 0;
        virtual void enqueue_impl(message_ptr, scheduler::execution_unit*) = 0;

        template<class F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        void execute();
        bool on(detail::string_view, handler*);

    private:
        handler_storage_t handlers_;
        const std::string type_;
        const int64_t id_;
    };

}} // namespace actor_zeta::base
