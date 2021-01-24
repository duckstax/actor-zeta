#pragma once

#include <abstract_actor.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/forwards.hpp>
#include "blocking_mail_queue.hpp"
#include "supervisor.hpp"

namespace actor_zeta {
///
/// @brief Specialization of actor with scheduling functionality
///
        class cooperative_actor
                : public abstract_actor
                , public executor::executable
                {
        public:

            using mailbox_type = blocking_mail_queue;



            ///TODO:
            //void launch(executor::execution_device *, bool /*hide*/) final;

            executor::executable_result run(executor::execution_device *, size_t max_throughput) final;

            ~cooperative_actor() override;

        protected:
            cooperative_actor(supervisor, detail::string_view);

            void enqueue_base(message, executor::execution_device *) final;

// message processing -----------------------------------------------------

            auto next_message() -> void ;

            auto current_message() -> message&;

            auto has_next_message() -> bool;

            auto mailbox() -> mailbox_type &;

            auto push_to_cache(message ) -> bool;

            auto pop_to_cache() -> message;

// ----------------------------------------------------- message processing
    private:
            message current_message_;
            std::unique_ptr<mailbox_type> mailbox_;
            supervisor supervisor_;
            executor::execution_device *executor_;
        };
}
