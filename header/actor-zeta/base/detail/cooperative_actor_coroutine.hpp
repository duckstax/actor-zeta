#pragma once

#include "traits_actor.hpp"
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/behavior.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/scheduler/resumable.hpp>

namespace actor_zeta { namespace base {

    template<class Supervisor, class Traits>
    class cooperative_actor<Supervisor, Traits, actor_type::coroutine>
        : public actor_abstract
        , public scheduler::resumable
        , public intrusive_behavior_t {
    public:
        scheduler::resume_result resume(scheduler::execution_unit* e, size_t max_throughput) final {
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
                inbox().fetch_more();
                auto prev_handled_msgs = handled_msgs;
                high(inbox()).new_round(quantum * 3, handle_async);
                normal(inbox()).new_round(quantum, handle_async);
                if (handled_msgs == prev_handled_msgs && inbox().try_block()) {
                    return scheduler::resume_result::awaiting;
                }
            }
            if (inbox().try_block()) {
                return scheduler::resume_result::awaiting;
            }
            return scheduler::resume_result::resume;
        }

        ~cooperative_actor() override {}

        void intrusive_ptr_add_ref_impl() final {
            ref();
        }

        void intrusive_ptr_release_impl() final {
            deref();
        }

    protected:
        cooperative_actor(Supervisor* ptr, std::string type)
            : actor_abstract(std::move(type))
            , supervisor_(ptr)
            , inbox_(mailbox::priority_message(),
                     high_priority_queue(mailbox::high_priority_message()),
                     normal_priority_queue(mailbox::normal_priority_message())) {
            inbox().try_block(); //todo: bug
        }

        template<class T>
        typename Traits::template allocator_type<T> get_allocator() const noexcept {
            return Traits::template allocator_type<T>(supervisor().resource());
        }

        detail::pmr::memory_resource* get_resource() const noexcept {
            return supervisor().resource();
        }

        void enqueue_impl(mailbox::message_ptr msg, scheduler::execution_unit* e) final {
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

        auto current_message() -> mailbox::message* {
            return current_message_;
        }

        auto set_current_message(mailbox::message_ptr msg) -> void {
            current_message_ = msg.release();
        }

    private:
        inline traits::inbox_t& inbox() {
            return inbox_;
        }

        bool activate(scheduler::execution_unit* ctx) {
            //assert(ctx != nullptr);
            if (ctx) {
                context(ctx);
            }
            return true;
        }

        auto reactivate(mailbox::message& x) -> void {
            current_message_ = &x;
            execute(this, current_message());
        }

        auto context(scheduler::execution_unit* e) -> void {
            if (e != nullptr) {
                executor_ = e;
            }
        }

        auto context() const -> scheduler::execution_unit* {
            return executor_;
        }

        auto supervisor() -> supervisor_abstract* {
            return supervisor_;
        }

        supervisor_abstract* supervisor_;
        scheduler::execution_unit* executor_;
        mailbox::message* current_message_;
        typename Traits::inbox_t inbox_;
    };

}} // namespace actor_zeta::base
