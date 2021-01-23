#pragma once

#include <set>
#include <unordered_map>
#include <memory>

#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/forwards.hpp>
#include <dispatcher.hpp>

namespace actor_zeta {

    class communication_module {
    public:
        communication_module() = delete;

        communication_module(const communication_module&) = delete;

        communication_module& operator=(const communication_module&) = delete;

        virtual ~communication_module();

        auto type() const -> abstract;

        auto message_types() const -> std::set<std::string>;

    protected:

        communication_module(detail::string_view, abstract);

        auto broadcast(message) -> bool;

        auto addresses(detail::string_view) -> address_t&;

        auto self() -> address_t;

        template<class F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            dispatcher_.on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            dispatcher_.on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        /**
           * debug method
           */
        auto all_view_address() const -> void;

            auto dispatch() -> dispatcher_t &;

            auto dispatch() const -> const dispatcher_t &;

    private:
        void add_link(const address_t&);

        void remove_link(const address_t&);

        void initialize();
        using contacts_type = std::unordered_map<detail::string_view, address_t>;
        std::unique_ptr<contacts_type> contacts_;
        dispatcher_t dispatcher_;
        std::size_t id_;
        abstract type_;
        detail::string_view name_;
    };
} // namespace actor_zeta
