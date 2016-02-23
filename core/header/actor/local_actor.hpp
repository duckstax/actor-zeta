#ifndef LOCAL_ACTOR_HPP
#define LOCAL_ACTOR_HPP

#include <memory>
#include "abstract_actor.hpp"
#include "standard_handlers/sync_contacts.hpp"
#include "messaging/mail_box.hpp"
#include "actor.hpp"
#include "behavior.hpp"
#include "forwards.hpp"
#include "executor/executable.hpp"

namespace actor_zeta {
    class local_actor : public executable, public abstract_actor {
    public:
        using mailbox_type=messaging::mail_box<messaging::message>;

        local_actor(const std::string &, behavior, abstract_coordinator_ptr);

        local_actor(const std::string &, abstract_coordinator_ptr);

        bool async_send(messaging::message &&) override;

        bool async_send(messaging::message &&, executor_ptr) override;

        void launch();

        virtual ~local_actor(){}

    protected:
        void attach_to_scheduler() override;

        void detach_from_scheduler() override;

        messaging::message next_message();

        void exect_event(messaging::message&&);

        void shedule(executor_ptr e);

        executable::state run(size_t max_throughput) override;

        behavior life;
        book_contacts contacts;
        std::unique_ptr<mailbox_type> mailbox;
    };

    inline actor spawn(
            const std::string &name,
            behavior live
    ) {
        live.insert("sync_contacts", actor_zeta::sync_contacts());
        return actor(new local_actor(name, live, nullptr));
    };

    inline actor spawn(
            const std::string &name,
            behavior live,
            abstract_coordinator_ptr e
    ) {
        live.insert("sync_contacts", actor_zeta::sync_contacts());
        return actor(new local_actor(name, live, e));
    };

}
#endif //LOCAL_ACTOR_HPP
