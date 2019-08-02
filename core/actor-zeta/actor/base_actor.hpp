#pragma once

#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/actor/dispatcher.hpp>

namespace actor_zeta { namespace actor {

        class base_actor
                : public abstract_actor
                , public context_t {
        public:
            ~base_actor() override;
            /**
            * debug method
            */
            auto all_view_address() const -> void;

            auto message_types() const -> std::set<std::string> final;
        protected:
            base_actor(detail::string_view);

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
            dispatcher_t dispatcher_;

        };

}}