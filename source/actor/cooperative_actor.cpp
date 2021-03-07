#include <iostream>
#include <cassert>

// clang-format off
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/base/cooperative_actor.hpp>
// clang-format on

namespace actor_zeta { namespace base {

        inline void error(){
            std::cerr << " WARNING " << std::endl;
            std::cerr << " WRONG ADDRESS " << std::endl;
            std::cerr << " WARNING " << std::endl;
        }

        executor::executable_result cooperative_actor::run(executor::execution_device* e, size_t max_throughput) {
            if (!activate(e)) {
                return executor::executable_result::done;
            }

            size_t handled_msgs = 0;

            message_ptr ptr;
            while (handled_msgs < max_throughput) {
                do {
                    ptr = next_message();
                    if (!ptr) {
                        if (mailbox().try_block()) {
                            return executor::executable_result::awaiting;
                        }
                    }
                } while (!ptr);
                reactivate(*ptr);
                ++handled_msgs;
                // iterate cache to see if we are now able
                // to process previously skipped messages
                while (consume_from_cache()) {
                    ++handled_msgs;
                }
                break;
            }

            if (!has_next_message() && mailbox().try_block()) {
                return executor::executable_result::awaiting;
            }
            // time's up
            return executor::executable_result::awaiting;
        }

        void cooperative_actor::enqueue(message_ptr msg, executor::execution_device *e) {
            assert(msg);
            mailbox().enqueue(msg.release());
            if(flags() == static_cast<int>(state::empty)) {
                intrusive_ptr_add_ref(this);
                if (e != nullptr) {
                    context(e);
                    context()->execute(this);
                } else {
                    env().executor().execute(this);
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
                        env().executor().execute(this);
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
                  supervisor &env
                , detail::string_view name
        )
                : abstract_actor(env, name)
        {
            flags(static_cast<int>(state::empty));
            mailbox().try_unblock();
        }


        cooperative_actor::~cooperative_actor(){

        }


        bool cooperative_actor::activate(executor::execution_device * ctx) {
            assert(ctx != nullptr);
            context(ctx);
            return true;
        }

        auto cooperative_actor::reactivate(message& x) -> void {
                consume(x);
        }


message_ptr cooperative_actor::next_message() {
    // we partition the mailbox into four segments in this case:
    // <-------- ! was_skipped --------> | <--------  was_skipped  -------->
    // <-- high prio --><-- low prio --> | <-- high prio --><-- low prio -->
    auto& cache = mailbox().cache();
    auto i = cache.begin();
    auto e = cache.separator();
    // read elements from mailbox if we don't have a high
    // priority message or if cache is empty
    if (i == e || !i->is_high_priority()) {
        // insert points for high priority
        auto hp_pos = i;
        // read whole mailbox at once
        auto tmp = mailbox().try_pop();
        while (tmp != nullptr) {
            cache.insert(tmp->is_high_priority() ? hp_pos : e, tmp);
            // adjust high priority insert point on first low prio element insert
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
    auto high_prio = [](const message& val) {
      return val.is_high_priority();
    };
    auto& cache = mailbox().cache();
    auto e = cache.end();
    cache.insert(std::partition_point(cache.continuation(),e, high_prio),ptr.release());
}

void cooperative_actor::consume(message& x) {
    current_message_ = &x;
    execute(*this);

}

bool cooperative_actor::consume_from_cache() {
    auto& cache = mailbox().cache();
    auto i = cache.continuation();
    auto e = cache.end();
    while (i != e) {
        cache.erase(i);
        return true;
    }
    return false;
}

void cooperative_actor::cleanup() {}

auto cooperative_actor::current_message() -> message* {
    return current_message_;
}

}}

