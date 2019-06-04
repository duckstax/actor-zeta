#pragma once

#include <memory>
#include <unordered_map>

#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/channel/channel.hpp>
#include <actor-zeta/actor/dispatcher.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief A generic actor
///
        class local_actor :
                public abstract_actor ,
                public context_t {
        public:

            virtual void launch(executor::execution_device*, bool /*hide*/) = 0;

            /*
            * debug method
            */
            auto all_view_address() const -> void;

            auto message_types() const -> std::set<std::string> final;

            ~local_actor() override ;

        protected:

            auto addresses(actor_address) -> void final;

            auto channel(channel::channel) -> void final;

            auto addresses(const std::string&)-> actor_address& final;

            auto channel(const std::string&)->channel::channel& final;

            auto self()  -> actor_address override;

            auto attach(executor::execution_device *e) -> void;

            auto attach() const -> executor::execution_device* ;

            template<std::size_t N, typename F>
            auto add_handler(const char(&name)[N], F &&f) -> void {
                dispatch().on(detail::string_view(name), make_handler(std::forward<F>(f)));
            }

            auto dispatch() -> dispatcher_t& {
                return dispatcher_;
            }

            auto dispatch() const  -> const dispatcher_t& {
                return dispatcher_;
            }

            local_actor(environment::abstract_environment *,  const std::string &);

        private:
            void initialize();

            std::unordered_map<std::string, actor_address> contacts;
            std::unordered_map<std::string, channel::channel> channels;
            dispatcher_t dispatcher_;
            executor::execution_device *executor_;
        };
    }
}
