#pragma once

#include <set>
#include <unordered_map>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/base/metadata.hpp>
#include <actor-zeta/base/dispatcher.hpp>
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/detail/callable_trait.hpp>


namespace actor_zeta { namespace base {

        class communication_module
                : public ref_counted
                , public context {
        public:

            communication_module() = delete;

            communication_module(const communication_module &) = delete;

            communication_module &operator=(const communication_module &) = delete;

            ~communication_module() override;

            actor_address address() const noexcept;

            auto type() const -> abstract;

            auto name() const -> detail::string_view;

            auto message_types() const -> std::set<std::string>;

            auto enqueue(messaging::message) -> void;

            virtual void enqueue(messaging::message, executor::execution_device *) = 0;

        protected:
            communication_module(detail::string_view, abstract);

            auto broadcast(messaging::message) -> bool;

            auto addresses(detail::string_view) -> actor_address & override;

            auto self() -> actor_address override ;

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
            void add_link(actor_address);

            void remove_link(const actor_address&);

            void initialize();

            std::unique_ptr<std::unordered_map<detail::string_view, actor_address>> contacts_;
            dispatcher_t dispatcher_;
            metadata type_;
        };
}}
