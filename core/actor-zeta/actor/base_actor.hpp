#pragma once

#include <memory>
#include <unordered_map>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/dispatcher.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief A generic actor
///
        class base_actor
                : public abstract_actor
                , public context_t {
        public:
            ~base_actor() override;
        protected:
            /**
            * debug method
            */
            auto all_view_address() const -> void;

            base_actor(detail::string_view name);

            /// sync -> async
            void add_link(actor_address);
            /// sync -> async
            void remove_link(const actor_address&);
            /// sync -> async
            void remove_link(detail::string_view);

            auto message_types() const -> std::set<std::string> final;

            auto addresses(detail::string_view) -> actor_address & final;

            auto self() -> actor_address override;

            template<std::size_t N, typename F>
            inline auto add_handler(const char(&name)[N], F &&f) -> void {
                dispatch().on(detail::string_view(name), make_handler(std::forward<F>(f)));
            }

            auto dispatch() -> dispatcher_t &;

            auto dispatch() const -> const dispatcher_t &;

            std::unordered_map<detail::string_view, actor_address> contacts;

        private:
            void initialize();

            dispatcher_t dispatcher_;

        };

}}