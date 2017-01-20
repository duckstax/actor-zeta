#ifndef LOCAL_ACTOR_HPP
#define LOCAL_ACTOR_HPP

#include <memory>

#include "actor-zeta/messaging/blocking_mail_queue.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "abstract_actor.hpp"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/forwards.hpp"
#include "actor-zeta/executor/executable.hpp"
#include "actor-zeta/contacts/book_contacts.hpp"

namespace actor_zeta {
    namespace actor {
        class local_actor : public abstract_actor {
        public:
            using mailbox_type = messaging::blocking_mail_queue<messaging::message>;
                                                            //hide
            virtual void launch(executor::execution_device*, bool) = 0;

            virtual ~local_actor();

        protected:
            inline void device(executor::execution_device* e) {
                executor_ = e;
            }

            inline executor::execution_device* device() const {
                return executor_;
            }

            void attach(behavior::abstract_action *);

            local_actor(environment::environment *, const std::string &);

            virtual void initialize();

// message processing -----------------------------------------------------

            messaging::message* next_message();

            bool has_next_message();

            inline mailbox_type &mailbox() {
                return mailbox_;
            }

            bool push_to_cache(messaging::message *);

            messaging::message* pop_to_cache();

// ----------------------------------------------------- message processing
            contacts::book_contacts contacts;
            behavior::behavior life;
        private:
            mailbox_type mailbox_;
            executor::execution_device *executor_;
        };
    }
}
#endif //LOCAL_ACTOR_HPP
