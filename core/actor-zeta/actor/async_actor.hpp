#ifndef SCHEDULED_ACTOR_HPP
#define SCHEDULED_ACTOR_HPP

#include <actor-zeta/messaging/mail_box.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/actor/local_actor.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/executor/executable.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Specialization of actor with scheduling functionality
///
        class async_actor :
                public local_actor,
                public executor::executable {
        public:

            using mailbox_type = messaging::mail_box;

            bool send(messaging::message&&) final;

            bool send(messaging::message&&, executor::execution_device *) final;

            void launch(executor::execution_device *, bool) final;

            executor::executable_result run(executor::execution_device *, size_t max_throughput) final;

            virtual ~async_actor();

        protected:
            async_actor(environment::abstract_environment *, mailbox_type*, const std::string &);

            void attach_to_scheduler() final;

            void detach_from_scheduler() final;

        private:

// message processing -----------------------------------------------------

            messaging::message next_message();

            bool has_next_message();

            mailbox_type &mailbox();

            bool push_to_cache(messaging::message&&);

            messaging::message pop_to_cache();

// ----------------------------------------------------- message processing

            std::unique_ptr<mailbox_type> mailbox_;
        };
    }
}
#endif //SCHEDULED_ACTOR_HPP
