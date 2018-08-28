#ifndef LOCAL_ACTOR_HPP
#define LOCAL_ACTOR_HPP

#include <memory>
#include <unordered_map>

#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/behavior/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/channel/channel.hpp>
#include <actor-zeta/behavior/reactions.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief A generic actor
///
        class local_actor :
                public abstract_actor ,
                public behavior::context_t {
        public:
                                                            //hide
            virtual void launch(executor::execution_device*, bool) = 0;

            /*
            * debug method
            */
            auto all_view_address() const -> void;

            auto message_types() const -> std::set<std::string> final;

            virtual ~local_actor();

        protected:

            void address(actor_address) final;

            void channel(channel::channel) final;

            auto address(const std::string&)-> actor_address& final;

            auto channel(const std::string&)->channel::channel& final;

            void device(executor::execution_device* e);

            executor::execution_device* device() const;

            void attach(behavior::abstract_action *);

            local_actor(environment::abstract_environment *,  const std::string &);

            virtual void initialize();
            

        protected:
            behavior::reactions reactions_;
            std::unordered_map<std::string, actor_address> contacts;
            std::unordered_map<std::string, channel::channel> channels;
        private:
            executor::execution_device *executor_;
        };
    }
}
#endif //LOCAL_ACTOR_HPP
