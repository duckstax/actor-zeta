#pragma once

#include <cassert>

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/base/cooperative_actor.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    scheduler::resume_result cooperative_actor::resume(scheduler::execution_unit* e, size_t max_throughput) {
        if (!activate(e)) {
            return scheduler::resume_result::done;
        }
        static constexpr size_t quantum = 3;
        size_t handled_msgs = 0;
        message_ptr ptr{nullptr, detail::pmr::deleter_t(resource())};

        auto handle_async = [this, max_throughput, &handled_msgs](message& x) -> detail::task_result {
            reactivate(x);
            return ++handled_msgs < max_throughput
                       ? detail::task_result::resume
                       : detail::task_result::stop_all;
        };

        while (handled_msgs < max_throughput) {
            inbox().fetch_more();
            auto prev_handled_msgs = handled_msgs;
            get_high_priority_queue().new_round(quantum * 3, handle_async);
            get_normal_priority_queue().new_round(quantum, handle_async);
            if (handled_msgs == prev_handled_msgs && inbox().try_block()) {
                return scheduler::resume_result::awaiting;
            }
        }
        if (inbox().try_block()) {
            return scheduler::resume_result::awaiting;
        }
        return scheduler::resume_result::resume;
    }

    void cooperative_actor::enqueue_impl(mailbox::message_ptr msg, scheduler::execution_unit* e) {
        assert(msg);
        switch (inbox().push_back(std::move(msg))) {
            case detail::enqueue_result::unblocked_reader: {
                intrusive_ptr_add_ref(this);
                if (e != nullptr) {
                    context(e);
                    context()->execute_later(this);
                } else {
                    supervisor()->scheduler()->enqueue(this);
                }
                break;
            }
            case detail::enqueue_result::success:
                break;
            case detail::enqueue_result::queue_closed:
                break;
        }
    }

    void cooperative_actor::intrusive_ptr_add_ref_impl() {
        ref();
    }

    void cooperative_actor::intrusive_ptr_release_impl() {
        deref();
    }

    cooperative_actor::cooperative_actor(supervisor_abstract* supervisor, std::string type)
        : actor_abstract(std::move(type))
        , intrusive_behavior_t(supervisor->resource())
        , supervisor_(supervisor)
        , inbox_(resource(),
            mailbox::priority_message(),
            high_priority_queue(resource(), mailbox::high_priority_message()),
            normal_priority_queue(resource(), mailbox::normal_priority_message())) {
        inbox().try_block(); //todo: bug
    }

    cooperative_actor::~cooperative_actor() {}

    bool cooperative_actor::activate(scheduler::execution_unit* ctx) {
        //assert(ctx != nullptr);
        if (ctx) {
            context(ctx);
        }
        return true;
    }

    auto cooperative_actor::reactivate(mailbox::message& x) -> void {
        current_message_ = &x;
        execute(this, current_message());
    }

    auto cooperative_actor::current_message() -> mailbox::message* {
        return current_message_;
    }

    auto cooperative_actor::set_current_message(mailbox::message_ptr msg) -> void {
        current_message_ = msg.release();
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
        return std::get<high_priority_queue_index>(inbox().queue().queues());
    }

    auto cooperative_actor::get_normal_priority_queue() -> normal_priority_queue& {
        return std::get<normal_priority_queue_index>(inbox().queue().queues());
    }

}} // namespace actor_zeta::base
