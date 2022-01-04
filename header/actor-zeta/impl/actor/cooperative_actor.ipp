#pragma once
#include <cassert>
#include <iostream>

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/base/actor_cooperative.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    inline void error() {
        std::cerr << " WARNING " << std::endl;
        std::cerr << " WRONG ADDRESS " << std::endl;
        std::cerr << " WARNING " << std::endl;
    }

    scheduler::resume_result actor_cooperative_t::resume(scheduler::execution_unit* e, size_t max_throughput) {
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

    void actor_cooperative_t::enqueue_impl(message_ptr msg, scheduler::execution_unit* e) {
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

    void actor_cooperative_t::intrusive_ptr_add_ref_impl() {
        flags(static_cast<int>(state::busy));
        mailbox().try_block();
        ref();
    }

    void actor_cooperative_t::intrusive_ptr_release_impl() {
        flags(static_cast<int>(state::empty));
        mailbox().try_unblock();
        deref();
    }

    actor_cooperative_t::actor_cooperative_t(
        supervisor_abstract* supervisor,
        std::string type, int64_t id)
        : actor_abstract(std::move(type), id)
        , supervisor_(supervisor) {
        flags(static_cast<int>(state::empty));
        mailbox().try_unblock();
    }

    actor_cooperative_t::~actor_cooperative_t() {}

    bool actor_cooperative_t::activate(scheduler::execution_unit* ctx) {
        assert(ctx != nullptr);
        if (ctx) {
            context(ctx);
        }
        return true;
    }

    auto actor_cooperative_t::reactivate(message& x) -> void {
        consume(x);
    }

    message_ptr actor_cooperative_t::next_message() {
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

    bool actor_cooperative_t::has_next_message() {
        auto& mbox = mailbox();
        auto& cache = mbox.cache();
        return cache.begin() != cache.separator() || mbox.can_fetch_more();
    }

    void actor_cooperative_t::push_to_cache(message_ptr ptr) {
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

    void actor_cooperative_t::consume(message& x) {
        current_message_ = &x;
        behavior_.execute(this,current_message_);
    }

    bool actor_cooperative_t::consume_from_cache() {
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

    void actor_cooperative_t::cleanup() {}

    auto actor_cooperative_t::current_message() -> message* {
        return current_message_;
    }

    scheduler::execution_unit* actor_cooperative_t::context() const {
        return executor_;
    }

    void actor_cooperative_t::context(scheduler::execution_unit* e) {
        if (e != nullptr) {
            executor_ = e;
        }
    }

    auto actor_cooperative_t::supervisor() -> supervisor_abstract* {
        return supervisor_;
    }
    auto actor_cooperative_t::clock() noexcept -> clock::clock_t& {
        return supervisor()->clock();
    }

}} // namespace actor_zeta::base
