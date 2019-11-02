#pragma once

#include <set>
#include <unordered_map>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/actor/metadata.hpp>
#include <actor-zeta/actor/dispatcher.hpp>


namespace actor_zeta { namespace actor {

        class message_passing_interface : public ref_counted {
        public:

            message_passing_interface() = delete;

            message_passing_interface(const message_passing_interface &) = delete;

            message_passing_interface &operator=(const message_passing_interface &) = delete;

            ~message_passing_interface() override;

            message_passing_interface(detail::string_view,abstract);

            auto enqueue(messaging::message) -> void;

            virtual void enqueue(messaging::message, executor::execution_device *) = 0;

            auto message_types() const -> std::set<std::string>;

            auto addresses(detail::string_view) -> actor_address &;

            auto self() -> actor_address ;

            actor_address address() const noexcept;

            template<typename F>
            inline auto add_handler(detail::string_view name, F &&f) -> void {
                dispatch().on(name, make_handler(std::forward<F>(f)));
            }

            /**
           * debug method
           */
            auto all_view_address() const -> void ;

            auto dispatch() -> dispatcher_t &;

            auto dispatch() const -> const dispatcher_t &;

            auto type() const -> abstract;

            auto name() const -> detail::string_view;

        protected:
            std::unordered_map<detail::string_view, actor_address> contacts;
            dispatcher_t dispatcher_;
            metadata type_;

        };
}}
