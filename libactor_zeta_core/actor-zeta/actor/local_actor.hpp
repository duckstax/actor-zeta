#ifndef LOCAL_ACTOR_HPP
#define LOCAL_ACTOR_HPP

#include <memory>
#include <unordered_map>

#include <actor-zeta/messaging/mail_box.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/behavior/abstract_behavior.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/behavior/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/channel/channel.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief A generic actor
///
        class local_actor :
                public abstract_actor ,
                public behavior::context_t {
        public:
            using mailbox_type = messaging::mail_box;
                                                            //hide
            virtual void launch(executor::execution_device*, bool) = 0;

            /*
            * debug method
            */
            auto all_view_address() const -> void;

            virtual ~local_actor();

        protected:

            void address(actor_address);

            void channel(channel::channel);

            auto address(const std::string&)-> actor_address&;

            auto channel(const std::string&)->channel::channel&;

            void device(executor::execution_device* e);

            executor::execution_device* device() const;

            void attach(behavior::abstract_action *);

            local_actor(environment::abstract_environment *,mailbox_type*, behavior::abstract_behavior *, const std::string &);

            virtual void initialize();

            virtual void startup(); /// virtual constructor

            virtual void shutdown(); /// virtual deconstructor

// message processing -----------------------------------------------------

            messaging::message next_message();

            bool has_next_message();

            mailbox_type &mailbox();

            bool push_to_cache(messaging::message&&);

            messaging::message pop_to_cache();

// ----------------------------------------------------- message processing
        protected:
            std::unique_ptr<behavior::abstract_behavior>life;
            std::unordered_map<std::string, actor_address> contacts;
            std::unordered_map<std::string, channel::channel> channels;
        private:           
            std::unique_ptr<mailbox_type> mailbox_;
            executor::execution_device *executor_;
        };
    }
}
#endif //LOCAL_ACTOR_HPP
