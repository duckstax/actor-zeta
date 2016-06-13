#include <utility>
#include "actor-zeta/actor/blocking_actor.hpp"
#include "actor-zeta/executor/executor_service.hpp"
#include "actor-zeta/executor/abstract_coordinator.hpp"

namespace actor_zeta {


    local_actor::local_actor(const std::string &type, abstract_coordinator *ptr)
            : abstract_actor(type, ptr) {
        init();
    }

    void local_actor::init() {
        life.insert("sync_contacts", new actor_zeta::sync_contacts(contacts));
    }

    bool local_actor::async_send(messaging::message &&document) {
        return async_send(std::move(document), nullptr);
    }

    bool local_actor::async_send(messaging::message &&document, executor_service *e) {
        bool status = mailbox.put(std::move(document));
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
            if (mailbox.empty()) {
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

    void local_actor::shedule(executor_service *e) {
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
        life.run(std::move(msg));
    }

    messaging::message local_actor::next_message() {
        return mailbox.get();
    }
}