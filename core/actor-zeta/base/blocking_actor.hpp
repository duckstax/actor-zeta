#pragma once

#include <mutex>
#include <condition_variable>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/base/abstract_actor.hpp>
#include <actor-zeta/messaging/mail_box.hpp>

namespace actor_zeta { namespace base {

///
/// @brief Specialization of base with blocking mode
///
        class blocking_actor
                : public abstract_actor
                , executor::executable {
        public:

            using mailbox_type = messaging::mail_box;

            blocking_actor(supervisor&, detail::string_view,mailbox_type*);
            executor::executable_result run(executor::execution_device *, size_t) final;
            ///TODO:
            ///void launch(executor::execution_device *,bool) final ;
            ~blocking_actor() override;

            messaging::message next_message();

            mailbox_type &mailbox();

        private:
            std::unique_ptr<mailbox_type> mailbox_;
        };
}}
