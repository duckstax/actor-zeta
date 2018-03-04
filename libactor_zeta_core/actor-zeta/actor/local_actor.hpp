#ifndef LOCAL_ACTOR_HPP
#define LOCAL_ACTOR_HPP

#include <memory>

#include "actor-zeta/messaging/mail_box.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "abstract_actor.hpp"
#include "actor-zeta/behavior/abstract_behavior.hpp"
#include "actor-zeta/forwards.hpp"
#include "actor-zeta/executor/executable.hpp"
#include "actor-zeta/contacts/book_contacts.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief A generic actor
///
        class local_actor : public abstract_actor {
        public:
            using mailbox_type = messaging::mail_box;
                                                            //hide
            virtual void launch(executor::execution_device*, bool) = 0;

            virtual ~local_actor();

        protected:
            void device(executor::execution_device* e);

            executor::execution_device* device() const;

            void attach(behavior::abstract_action *);

            local_actor(environment::abstract_environment *,mailbox_type*, behavior::abstract_behavior *, const std::string &);

            virtual void initialize();

// message processing -----------------------------------------------------

            messaging::message next_message();

            bool has_next_message();

            mailbox_type &mailbox();

            bool push_to_cache(messaging::message&&);

            messaging::message pop_to_cache();

// ----------------------------------------------------- message processing
        protected:
            contacts::book_contacts contacts;
            std::unique_ptr<behavior::abstract_behavior>life;
        private:
            std::unique_ptr<mailbox_type> mailbox_;
            executor::execution_device *executor_;
        };
    }
}
#endif //LOCAL_ACTOR_HPP
