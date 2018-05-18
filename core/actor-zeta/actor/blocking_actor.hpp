#ifndef BLOCKING_ACTOR_HPP
#define BLOCKING_ACTOR_HPP

#include <mutex>
#include <condition_variable>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/actor/local_actor.hpp>
#include <actor-zeta/messaging/mail_box.hpp>

namespace actor_zeta { namespace actor {

///
/// @brief Specialization of actor with blocking mode
///
        class blocking_actor  :
                public local_actor ,
                executor::executable {
        public:

            using mailbox_type = messaging::mail_box;

            blocking_actor(environment::abstract_environment *,mailbox_type* , const std::string &);
            executor::executable_result run(executor::execution_device *, size_t) override final;
            void launch(executor::execution_device *,bool) override final ;
            virtual ~blocking_actor();

            messaging::message next_message();

            mailbox_type &mailbox();

        private:
            std::unique_ptr<mailbox_type> mailbox_;
        };
    }
}
#endif //BLOCKING_ACTOR_HPP
