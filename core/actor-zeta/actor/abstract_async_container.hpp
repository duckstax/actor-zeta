#pragma once

#include <set>
#include <unordered_map>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/actor/metadata.hpp>
#include <actor-zeta/actor/dispatcher.hpp>
#include <actor-zeta/actor/context.hpp>


namespace actor_zeta { namespace actor {

        class abstract_async_container
                : public ref_counted
                , public context {
        public:

            abstract_async_container() = delete;

            abstract_async_container(const abstract_async_container &) = delete;

            abstract_async_container &operator=(const abstract_async_container &) = delete;

            ~abstract_async_container() override;

            actor_address address() const noexcept;

            auto type() const -> abstract;

            auto name() const -> detail::string_view;

            auto message_types() const -> std::set<std::string>;

            auto enqueue(messaging::message) -> void;

            virtual void enqueue(messaging::message, executor::execution_device *) = 0;

        protected:
            abstract_async_container(detail::string_view, abstract);

            auto broadcast(messaging::message) -> bool;

            auto addresses(detail::string_view) -> actor_address & override;

            auto self() -> actor_address override ;

            template<typename F>
            auto add_handler(detail::string_view name, F &&f) -> void {
                dispatch().on(name, make_handler(std::forward<F>(f)));
            }

            /**
           * debug method
           */
            auto all_view_address() const -> void ;

            auto dispatch() -> dispatcher_t &;

            auto dispatch() const -> const dispatcher_t &;

            /// sync -> async
            void add_link(actor_address);
            /// sync -> async
            void remove_link(const actor_address&);
            /// sync -> async
            void remove_link(detail::string_view);

        private:
            void initialize();
            std::unique_ptr<std::unordered_map<detail::string_view, actor_address>> contacts_;
            dispatcher_t dispatcher_;
            metadata type_;

        };
}}
