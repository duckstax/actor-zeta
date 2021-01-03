#pragma once

#include <set>
#include <unordered_map>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/base/metadata.hpp>
#include <actor-zeta/base/dispatcher.hpp>
#include <actor-zeta/detail/callable_trait.hpp>


namespace actor_zeta { namespace base {

        class communication_module {
        public:

            communication_module() = delete;

            communication_module(const communication_module &) = delete;

            communication_module &operator=(const communication_module &) = delete;

            virtual ~communication_module();

            address_type address() const noexcept;

            auto type() const -> abstract;

            auto name() const -> detail::string_view;

            auto message_types() const -> std::set<std::string>;

            auto enqueue(messaging::message) -> void;

            void enqueue(messaging::message, executor::execution_device *);

        protected:
            virtual void enqueue_base(messaging::message, executor::execution_device *) = 0;

            communication_module(detail::string_view, abstract);

            auto broadcast(messaging::message) -> bool;

            auto addresses(detail::string_view) -> address_type&;

            auto self() -> address_type;

            template<class F>
            auto add_handler(detail::string_view name, F &&f) ->  typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
                dispatch().on(name, make_handler(std::forward<F>(f)));
            }

            template<typename F>
            auto add_handler(detail::string_view name, F &&f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
                dispatch().on(name, make_handler(std::forward<F>(f),static_cast<typename type_traits::get_callable_trait_t<F>::class_type *>(this)));
            }

            /**
           * debug method
           */
            auto all_view_address() const -> void ;

            auto dispatch() -> dispatcher_t &;

            auto dispatch() const -> const dispatcher_t &;

        private:
            void add_link(address_type);

            void remove_link(const address_type&);

            void initialize();
            using contacts_type =  std::unordered_map<detail::string_view, address_type>;
            std::unique_ptr<contacts_type> contacts_;
            dispatcher_t dispatcher_;
            metadata type_;
        };
}}
