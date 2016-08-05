#ifndef LOCAL_ACTOR_HPP
#define LOCAL_ACTOR_HPP

#include <memory>

#include "actor-zeta/messaging/blocking_mail_queue.hpp"
#include "abstract_actor.hpp"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/forwards.hpp"
#include "actor-zeta/executor/executable.hpp"
#include "actor-zeta/contacts/book_contacts.hpp"

namespace actor_zeta {
    namespace actor {
        class local_actor : public executor::executable, public abstract_actor {
        public:
            using mailbox_type=messaging::blocking_mail_queue<messaging::message>;

                                                             //hide
            virtual void launch(executor::execution_device *, bool);

            virtual ~local_actor() {}

            bool async_send(messaging::message &&) override;

            bool async_send(messaging::message &&, executor::execution_device *) override;

            inline void device(executor::execution_device *e) {
                executor_ = e;
            }

            inline executor::execution_device *device() const {
                return executor_;
            }

            void attach(behavior::interface_action *) override final;

        protected:
            local_actor(environment::environment &, const std::string &);

            virtual void initialize();
            virtual bool finalize();

            void attach_to_scheduler() override;

            void detach_from_scheduler() override;

            messaging::message next_message();

            void shedule(executor::execution_device *e);

            virtual executor::executable::executable_result
            run(executor::execution_device *, size_t max_throughput) override;

            contacts::book_contacts contacts;
            mailbox_type mailbox;
            behavior::behavior life;
        private:
            executor::execution_device *executor_;
        };
    }
}
#endif //LOCAL_ACTOR_HPP
