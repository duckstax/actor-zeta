#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/base/handler.hpp>

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

    class communication_module
        : public ref_counted {
    public:
        using key_type = detail::string_view;
        using handler_storage_t = std::unordered_map<key_type, std::unique_ptr<handler>>;

        communication_module() = delete;
        communication_module(const communication_module&) = delete;
        communication_module& operator=(const communication_module&) = delete;
        ~communication_module() override;

        auto type() const -> detail::string_view;
        auto message_types() const -> std::set<std::string>;
        auto enqueue(message_ptr) -> void;
        void enqueue(message_ptr, executor::execution_device*);
        auto current_message() -> message*;

    protected:
        communication_module(std::string);
        virtual auto current_message_impl() -> message* = 0;
        virtual void enqueue_base(message_ptr, executor::execution_device*) = 0;

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
    };

}} // namespace actor_zeta::base
