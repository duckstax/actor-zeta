#pragma once

#include "hfsm.hpp"
#include "traits_actor.hpp"
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/behavior.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/scheduler/resumable.hpp>
#include <actor-zeta/detail/type_traits.hpp>

namespace actor_zeta { namespace base {

    template<class Actor, class Traits>
    class cooperative_actor<Actor, Traits, actor_type::classic>
        : public actor_abstract
        , private scheduler::resumable {
    public:
        using mailbox_t = typename Traits::mailbox_t;
        scheduler::resume_result resume(scheduler::execution_unit* unit, size_t max_throughput) final {
            if (!activate(unit)) {
                return scheduler::resume_result::done;
            }
            size_t handled_msgs = 0;
            while (handled_msgs < max_throughput) {
                auto ptr = mailbox().pop_front();
                if (!ptr) {
                    if (mailbox().try_block()) {
                        return scheduler::resume_result::awaiting;
                    }
                    continue;
                }
                reactivate(*ptr);
                ++handled_msgs;
                return scheduler::resume_result::done;
            }

            if (mailbox().try_block()) {
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
        template<
            class Supervisor,class ...Args,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, Supervisor>::value>>// todo: check Supervisoar is a pointer
        cooperative_actor(Supervisor* ptr,Args&&... args)
            : actor_abstract()
            , supervisor_([](supervisor_abstract*ptr) { assert(ptr);return ptr; }(static_cast<supervisor_abstract*>(ptr)))
            , stack_(resource())
            , mailbox_(std::forward<Args>(args)...) {
            ///mailbox().try_block(); //todo: bug
        }

        const char* type_impl() const noexcept final {
            auto const *ptr = static_cast<const Actor*>(this);
            return ptr->make_type();
        }

        template<class T>
        typename Traits::template allocator_type<T> allocator() const noexcept {
            return Traits::template allocator_type<T>(supervisor().resource());
        }

        pmr::memory_resource* resource() const noexcept {
            return supervisor()->resource();
        }

        bool enqueue_impl(mailbox::message_ptr msg, scheduler::execution_unit* e) final {
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
                case detail::enqueue_result::queue_closed: {
                    return false ;
                }
                default: {
                    return false ;
                }
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

        inline mailbox_t& mailbox() {
            return mailbox_;
        }

        bool activate(scheduler::execution_unit* ctx) {
            assert(ctx != nullptr);
            if (ctx) {
                context(ctx);
            }
            return true;
        }

        auto reactivate(mailbox::message& x) -> void {
            current_message_ = &x;
            if (stack_.empty()) {
                stack_.emplace_back(std::move(self()->behavior()));
            } else {
                ///todo: coroutine support
            }

            auto& behavior = stack_.back();
            invoke(behavior,self(), current_message_);
        }

        auto context(scheduler::execution_unit* e) -> void {
            if (e != nullptr) {
                executor_ = e;
            }
        }

        auto context() const noexcept -> scheduler::execution_unit* {
            return executor_;
        }

        auto supervisor() noexcept -> supervisor_abstract* {
            return supervisor_;
        }

        auto supervisor() const noexcept -> const supervisor_abstract* {
            return supervisor_;
        }

        supervisor_abstract* supervisor_;
        detail::hfsm stack_;
        scheduler::execution_unit* executor_;
        mailbox::message* current_message_;
        mailbox_t mailbox_;
    };

}} // namespace actor_zeta::base
