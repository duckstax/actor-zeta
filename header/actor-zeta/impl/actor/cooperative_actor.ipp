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

        size_t handled_msgs = 0;

        message_ptr ptr;

        while (handled_msgs < max_throughput && !mailbox().cache().empty()) {
            do {
                ptr = next_message();
                if (!ptr) {
                    if (mailbox().try_block()) {
                        return scheduler::resume_result::awaiting;
                    }
                }
            } while (!ptr);
            consume_from_cache();
            ++handled_msgs;
        }

        while (handled_msgs < max_throughput) {
            do {
                ptr = next_message();
                if (!ptr) {
                    if (mailbox().try_block()) {
                        return scheduler::resume_result::awaiting;
                    }
                }
            } while (!ptr);
            reactivate(*ptr);
            ++handled_msgs;
        }

        while (!ptr) {
            ptr = next_message();
            push_to_cache(std::move(ptr));
        }

        if (!has_next_message() && mailbox().try_block()) {
            return scheduler::resume_result::awaiting;
        }

        return scheduler::resume_result::awaiting;
    }

    void cooperative_actor::enqueue_impl(message_ptr msg, scheduler::execution_unit* e) {
        assert(msg);
        mailbox().enqueue(msg.release());
        if (flags() == static_cast<int>(state::empty)) {
            intrusive_ptr_add_ref(this);
            if (e != nullptr) {
                context(e);
                context()->execute_later(this);
            } else {
                supervisor()->scheduler()->enqueue(this);
            }
        }

        /*
            switch ( mailbox().enqueue(msg.release())) {
                case detail::enqueue_result::unblocked_reader: {
                    intrusive_ptr_add_ref(this);
                    if (e != nullptr) {
                        context(e);
                        context()->execute(this);
                    } else {
                        env().scheduler().execute(this);
                    }
                    break;
                }
                case detail::enqueue_result::queue_closed: {
                    assert(false);
                    break;
                }
                case detail::enqueue_result::success:
                    break;
            }
             */
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
        std::string type, int64_t id)
        : actor_abstract(std::move(type), id)
        , supervisor_(supervisor) {
        flags(static_cast<int>(state::empty));
        mailbox().try_unblock();
    }

    cooperative_actor::~cooperative_actor() {}

    bool cooperative_actor::activate(scheduler::execution_unit* ctx) {
        assert(ctx != nullptr);
        if (ctx) {
            context(ctx);
        }
        return true;
    }

    auto cooperative_actor::reactivate(message& x) -> void {
        consume(x);
    }

    message_ptr cooperative_actor::next_message() {
        auto& cache = mailbox().cache();
        auto i = cache.begin();
        auto e = cache.separator();
        if (i == e || !i->is_high_priority()) {
            auto hp_pos = i;
            auto tmp = mailbox().try_pop();
            while (tmp != nullptr) {
                cache.insert(tmp->is_high_priority() ? hp_pos : e, tmp);
                if (hp_pos == e && !tmp->is_high_priority())
                    --hp_pos;
                tmp = mailbox().try_pop();
            }
        }
        message_ptr result;
        i = cache.begin();
        if (i != e)
            result.reset(cache.take(i));
        return result;
    }

    bool cooperative_actor::has_next_message() {
        auto& mbox = mailbox();
        auto& cache = mbox.cache();
        return cache.begin() != cache.separator() || mbox.can_fetch_more();
    }

    void cooperative_actor::push_to_cache(message_ptr ptr) {
        assert(ptr != nullptr);
        if (!ptr->is_high_priority()) {
            mailbox().cache().insert(mailbox().cache().end(), ptr.release());
            return;
        }
        auto high_priority = [](const message& val) {
            return val.is_high_priority();
        };
        auto& cache = mailbox().cache();
        auto e = cache.end();
        cache.insert(std::partition_point(cache.continuation(), e, high_priority), ptr.release());
    }

    void cooperative_actor::consume(message& x) {
        current_message_ = &x;
        behavior_.execute(this,current_message_);
    }

    bool cooperative_actor::consume_from_cache() {
        auto& cache = mailbox().cache();
        auto i = cache.continuation();
        auto e = cache.end();
        while (i != e) {
            consume(*i);
            cache.erase(i);
            return true;
        }
        return false;
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
    auto cooperative_actor::clock() noexcept -> clock::clock_t& {
        return supervisor()->clock();
    }

}} // namespace actor_zeta::base
