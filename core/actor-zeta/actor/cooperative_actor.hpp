#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/messaging/mail_box.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/executor/executable.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Specialization of actor with scheduling functionality
///
        class cooperative_actor
                : public abstract_actor
                , public executor::executable
                {
        public:

            using mailbox_type = messaging::mail_box;

            using abstract_async_container::enqueue;

            void enqueue(messaging::message, executor::execution_device *) final;

            ///TODO:
            //void launch(executor::execution_device *, bool /*hide*/) final;

            executor::executable_result run(executor::execution_device *, size_t max_throughput) final;

            ~cooperative_actor() override;

        protected:
            cooperative_actor(supervisor &, detail::string_view,mailbox_type*);

            void intrusive_ptr_add_ref_impl() override;

            void intrusive_ptr_release_impl() override;

        private:

// message processing -----------------------------------------------------

            auto next_message() -> void ;

            auto current_message() -> messaging::message& override;

            bool has_next_message();

            mailbox_type &mailbox();

            bool push_to_cache(messaging::message );

            messaging::message pop_to_cache();

// ----------------------------------------------------- message processing
            messaging::message current_message_;
            std::unique_ptr<mailbox_type> mailbox_;
        };
}}
