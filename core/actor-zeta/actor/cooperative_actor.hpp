#pragma once

#include <actor-zeta/messaging/mail_box.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/actor/executable_actor.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/executor/executable.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Specialization of actor with scheduling functionality
///
        class cooperative_actor :
                public executable_actor,
                public executor::executable {
        public:

            using mailbox_type = messaging::mail_box;

            using abstract_actor::enqueue;

            void enqueue(messaging::message, executor::execution_device *) final;

            ///TODO:
            //void launch(executor::execution_device *, bool /*hide*/) final;

            executor::executable_result run(executor::execution_device *, size_t max_throughput) final;

            ~cooperative_actor() override;

        protected:
            cooperative_actor(supervisor &, mailbox_type*, detail::string_view);

            void intrusive_ptr_add_ref_impl() override;

            void intrusive_ptr_release_impl() override;

        private:

// message processing -----------------------------------------------------

            messaging::message next_message();

            bool has_next_message();

            mailbox_type &mailbox();

            bool push_to_cache(messaging::message );

            messaging::message pop_to_cache();

// ----------------------------------------------------- message processing

            std::unique_ptr<mailbox_type> mailbox_;
        };
}}
