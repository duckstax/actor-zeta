#pragma once

#include "hfsm.hpp"
#include "traits_actor.hpp"
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/behavior.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/type_traits.hpp>
#include <actor-zeta/scheduler/resumable.hpp>
#include <actor-zeta/detail/memory.hpp>

namespace actor_zeta { namespace base {

    template<class Actor, class Traits>
    class cooperative_actor<Actor, Traits, actor_type::classic>
        : public actor_abstract
        , public scheduler::resumable {
    public:
        using uptr = std::unique_ptr<cooperative_actor<Actor, Traits, actor_type::classic>,actor_zeta::pmr::deleter_t>;

        scheduler::resume_result resume(size_t max_throughput) final {
            static constexpr size_t quantum = 3;
            size_t handled_msgs = 0;
            mailbox::message_ptr ptr;

            auto handle_async = [this, max_throughput, &handled_msgs](mailbox::message& x) -> detail::task_result {
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

        ~cooperative_actor() override = default;

        void intrusive_ptr_add_ref_impl() final {
            ref();
        }

        void intrusive_ptr_release_impl() final {
            deref();
        }

        template<class Target>
        static Target* check_ptr(Target* ptr) {
            assert(ptr);
            return ptr;
        }

    protected:
        cooperative_actor(pmr::memory_resource* in_resource)
            : actor_abstract(check_ptr(in_resource))
            , stack_(resource())
            , inbox_(mailbox::priority_message(),
                     high_priority_queue(mailbox::high_priority_message()),
                     normal_priority_queue(mailbox::normal_priority_message())) {
            inbox().try_block(); //todo: bug
        }

        auto type_impl() const noexcept -> const char* final {
            auto const* ptr = static_cast<const Actor*>(this);
            return ptr->make_type();
        }

        template<class T>
        typename Traits::template allocator_type<T> allocator() const noexcept {
            return Traits::template allocator_type<T>(resource());
        }

        void enqueue_impl(mailbox::message_ptr msg) final {
            assert(msg);
            switch (inbox().push_back(std::move(msg))) {
                case detail::enqueue_result::unblocked_reader: {
                    intrusive_ptr_add_ref(this);
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

        void become(behavior_t behavior) {
            become_impl(std::move(behavior), true);
        }

        void become(const keep_behavior_t&, behavior_t behavior) {
            become_impl(std::move(behavior), false);
        }

        void unbecome() {
            stack_.pop_back();
        }

    private:
        void become_impl(behavior_t behavior, bool discard_old) {
            if (discard_old && !stack_.empty()) {
                stack_.pop_back();
            }

            if (behavior) {
                stack_.push_back(std::move(behavior));
            }
        }

        bool has_behavior() const noexcept {
            return !stack_.empty();
        }

        behavior_t& current_behavior() {
            return stack_.back();
        }

        detail::hfsm& stack() {
            return stack_;
        }

        bool is_live() const noexcept {
            return !stack_.empty();
        }

        auto self() noexcept -> Actor* {
            return static_cast<Actor*>(this);
        }

        auto self() const noexcept -> Actor* {
            return static_cast<Actor*>(this);
        }

        inline traits::inbox_t& inbox() {
            return inbox_;
        }

        auto reactivate(mailbox::message& x) -> void {
            current_message_ = &x;
            if (stack_.empty()) {
                stack_.emplace_back(std::move(self()->behavior()));
            } else {
                ///todo: coroutine support
            }

            auto& behavior = stack_.back();
            invoke(behavior, self(), current_message_);
        }

        detail::hfsm stack_;
        mailbox::message* current_message_;
        typename Traits::inbox_t inbox_;
    };

}} // namespace actor_zeta::base
