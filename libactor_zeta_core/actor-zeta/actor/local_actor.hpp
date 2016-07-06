#ifndef LOCAL_ACTOR_HPP
#define LOCAL_ACTOR_HPP

#include <memory>
#include "actor-zeta/messaging/blocking_mail_queue.hpp"
#include "abstract_actor.hpp"
#include "actor-zeta/standard_handlers/sync_contacts.hpp"
#include "actor.hpp"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/forwards.hpp"
#include "actor-zeta/executor/executable.hpp"

namespace actor_zeta {
    namespace actor {
        class local_actor : public executable, public abstract_actor {
        public:
            using mailbox_type=messaging::blocking_mail_queue<messaging::message>;

            local_actor(const std::string &, abstract_coordinator *);

            bool async_send(messaging::message &&) override;

            bool async_send(messaging::message &&, executor_service *) override;

            void launch();

            virtual ~local_actor() {}

        protected:

            virtual void initialize();

            void attach_to_scheduler() override;

            void detach_from_scheduler() override;

            messaging::message next_message();

            void exect_event(messaging::message &&);

            void shedule(executor_service *e);

            executable::state run(size_t max_throughput) override;

            behavior::behavior life;
            contacts::book_contacts contacts;
            mailbox_type mailbox;
        };
    }
}
#endif //LOCAL_ACTOR_HPP
