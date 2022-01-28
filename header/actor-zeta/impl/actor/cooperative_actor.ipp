#pragma once
#include <cassert>
#include <iostream>

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/base/cooperative_actor.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    inline void error() {
        std::cerr << " WARNING " << std::endl;
        std::cerr << " WRONG ADDRESS " << std::endl;
        std::cerr << " WARNING " << std::endl;
    }

    executor::executable_result cooperative_actor::run(executor::execution_device* e, size_t max_throughput) {
        if (!activate(e)) {
            return executor::executable_result::done;
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
            get_urgent_queue().new_round(quantum * 3, handle_async);
            get_normal_queue().new_round(quantum, handle_async);
            if (handled_msgs == prev_handled_msgs && mailbox().try_block()) {
                return executor::executable_result::awaiting;
            }
        }
        if (mailbox().try_block()) {
            return executor::executable_result::awaiting;
        }
        return executor::executable_result::resume;
    }

    bool cooperative_actor::enqueue_impl(message_ptr msg, executor::execution_device* e) {
        assert(msg);
        switch (mailbox().push_back(std::move(msg))) {
            case detail::inbox_result::unblocked_reader: {
                intrusive_ptr_add_ref(this);
                if (e != nullptr) {
                    context(e);
                    context()->execute(this);
                } else {
                    supervisor()->executor()->execute(this);
                }
                return true;
            }
            case detail::inbox_result::queue_closed:
                return false;
            case detail::inbox_result::success:
                return true;
        }
        return true;
    }

    void cooperative_actor::intrusive_ptr_add_ref_impl() {
        flags(static_cast<int>(state::busy));
        mailbox().try_block();
        ref();
    }

    void cooperative_actor::intrusive_ptr_release_impl() {
        flags(static_cast<int>(state::empty));
        mailbox().try_unblock();
        deref();
    }

    cooperative_actor::cooperative_actor(
        supervisor_abstract* supervisor,
        std::string type,int64_t id)
        : actor_abstract(std::move(type),id)
        , supervisor_(supervisor)
        , mailbox_(mail_box::categorized(), mail_box::urgent_messages(), mail_box::normal_messages()) {
        flags(static_cast<int>(state::empty));
        mailbox().try_unblock();
    }

    cooperative_actor::~cooperative_actor() {}

    bool cooperative_actor::activate(executor::execution_device* ctx) {
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

    executor::execution_device* cooperative_actor::context() const {
        return executor_;
    }

    void cooperative_actor::context(executor::execution_device* e) {
        if (e != nullptr) {
            executor_ = e;
        }
    }

    auto cooperative_actor::supervisor() -> supervisor_abstract* {
        return supervisor_;
    }

    auto cooperative_actor::get_urgent_queue() -> urgent_queue& {
        return std::get<urgent_queue_index>(mailbox().queue().queues());
    }

    auto cooperative_actor::get_normal_queue() -> normal_queue& {
        return std::get<normal_queue_index>(mailbox().queue().queues());
    }

}} // namespace actor_zeta::base
