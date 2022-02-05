#pragma once
#include <cassert>
#include <iostream>

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/base/cooperative_actor.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    inline void error() {
        std::cerr << " WARNING " << std::endl;
        std::cerr << " WRONG ADDRESS " << std::endl;
        std::cerr << " WARNING " << std::endl;
    }

    scheduler::resume_result cooperative_actor::resume(scheduler::execution_unit* e, size_t max_throughput) {
        if (!activate(e)) {
            return scheduler::resume_result::done;
        }
        static constexpr size_t quantum = 3;
        size_t handled_msgs = 0;
        message_ptr ptr;

        auto handle_async = [this, max_throughput, &handled_msgs](message& x) -> detail::task_result {
            reactivate(x);
            return ++handled_msgs < max_throughput
                       ? detail::task_result::resume
                       : detail::task_result::stop_all;
        };

        while (handled_msgs < max_throughput) {
            mailbox().fetch_more();
            auto prev_handled_msgs = handled_msgs;
            get_high_priority_queue().new_round(quantum * 3, handle_async);
            get_normal_priority_queue().new_round(quantum, handle_async);
            if (handled_msgs == prev_handled_msgs && mailbox().try_block()) {
                return scheduler::resume_result::awaiting;
            }
        }
        if (mailbox().try_block()) {
            return scheduler::resume_result::awaiting;
        }
        return scheduler::resume_result::resume;
    }

    bool cooperative_actor::enqueue_impl(message_ptr msg, scheduler::execution_unit* e) {
        assert(msg);
        switch (mailbox().push_back(std::move(msg))) {
            case detail::enqueue_result::unblocked_reader: {
                intrusive_ptr_add_ref(this);
                if (e != nullptr) {
                    context(e);
                    context()->execute_later(this);
                } else {
                    supervisor()->scheduler()->enqueue(this);
                }
                return true;
            }
            case detail::enqueue_result::success:
                return true;
            case detail::enqueue_result::queue_closed:
                return false;
        }
        return true;
    }

    void cooperative_actor::intrusive_ptr_add_ref_impl() {
        ref();
    }

    void cooperative_actor::intrusive_ptr_release_impl() {
        deref();
    }

    cooperative_actor::cooperative_actor(
        supervisor_abstract* supervisor,
        std::string type,int64_t id)
        : actor_abstract(std::move(type),id)
        , supervisor_(supervisor)
        , mailbox_(mail_box::priority_message(), mail_box::high_priority_message(), mail_box::normal_priority_message()) {
        mailbox().try_block();
    }

    cooperative_actor::~cooperative_actor() {}

    bool cooperative_actor::activate(scheduler::execution_unit* ctx) {
        //assert(ctx != nullptr);
        if (ctx) {
            context(ctx);
        }
        return true;
    }

    auto cooperative_actor::reactivate(message& x) -> void {
        consume(x);
    }

    void cooperative_actor::consume(message& x) {
        current_message_ = &x;
        execute();
    }

    void cooperative_actor::cleanup() {}

    auto cooperative_actor::current_message_impl() -> message* {
        return current_message_;
    }

    scheduler::execution_unit* cooperative_actor::context() const {
        return executor_;
    }

    void cooperative_actor::context(scheduler::execution_unit* e) {
        if (e != nullptr) {
            executor_ = e;
        }
    }

    auto cooperative_actor::supervisor() -> supervisor_abstract* {
        return supervisor_;
    }

    auto cooperative_actor::get_high_priority_queue() -> high_priority_queue& {
        return std::get<high_priority_queue_index>(mailbox().queue().queues());
    }

    auto cooperative_actor::get_normal_priority_queue() -> normal_priority_queue& {
        return std::get<normal_priority_queue_index>(mailbox().queue().queues());
    }

}} // namespace actor_zeta::base
