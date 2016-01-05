#include <utility>
#include "actor/blocking_actor.hpp"
#include "executor/executor_service.hpp"
#include "actor/local_actor.hpp"
#include "messaging/blocking_mail_queue.hpp"
#include "executor/abstract_coordinator.hpp"

namespace actor_zeta {

    local_actor::local_actor(const std::string &type, behavior live, abstract_coordinator_ptr e)
            : abstract_actor(type, e),
              life(live),
              mailbox(new messaging::blocking_mail_queue<messaging::message>()) { }

    local_actor::local_actor(const std::string &type, abstract_coordinator_ptr ptr)
            : abstract_actor(type, ptr), mailbox(new messaging::blocking_mail_queue<messaging::message>()) { }

    bool local_actor::async_send(messaging::message &&document) {
        return async_send(std::move(document), nullptr);
    }

    bool local_actor::async_send(messaging::message &&document, executor_ptr e) {
        bool status = mailbox->put(std::move(document));
        // schedule actor
        shedule(e);
        return status;
    }

    void local_actor::attach_to_scheduler() {
        ref();
    }

    void local_actor::detach_from_scheduler() {
        deref();
    }

    executable::state local_actor::run(size_t max_throughput) {
        if (is_blocked()) {
            // actor lives in its own thread
            auto self = static_cast<blocking_actor *>(this);
            self->act();
            return state::done;
        }

        for (int i = 0; i < max_throughput; ++i) {
            if (mailbox->empty()) {
                auto msg = std::move(next_message());
                exect_event(std::move(msg));
            }
            else {
                return state::waiting;
            }
        }
        return state::done;
    };

    void local_actor::launch() {
        auto max_throughput = std::numeric_limits<size_t>::max();
        while (run(max_throughput) != state::waiting) { }
    };

    void local_actor::shedule(executor_ptr e) {
        // schedule actor
        if (e) {
            e->put_execute_latest(this);
        }
        else {
            if (_executor) {
                _executor->submit(this);
            }
            else {
                launch();
            }
        }
    }

    void local_actor::exect_event(messaging::message &&msg) {
        life.run(contacts, std::move(msg));
    }

    messaging::message local_actor::next_message() {
        return mailbox->get();
    }
}