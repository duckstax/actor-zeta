#pragma once

#include <actor-zeta/base/behavior.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/queue/fifo_inbox.hpp>
#include <actor-zeta/mailbox.hpp>
#include <actor-zeta/scheduler/resumable.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Specialization of actor with scheduling functionality
    ///

    class cooperative_actor
        : public actor_abstract
        , public scheduler::resumable
        , public intrusive_behavior_t {
    public:
        using inbox_t = detail::fifo_inbox<mailbox_policy>;

        scheduler::resume_result resume(scheduler::execution_unit*, max_throughput_t) final;

        ~cooperative_actor() override;

        void intrusive_ptr_add_ref_impl() override;
        void intrusive_ptr_release_impl() override;

    protected:
        template<class Supervisor>
        cooperative_actor(Supervisor* ptr, std::string type)
            : cooperative_actor(static_cast<supervisor_abstract*>(ptr), std::move(type)) {};

        void enqueue_impl(mailbox::message_ptr, scheduler::execution_unit*);

        auto current_message() -> mailbox::message* ;
        auto set_current_message(mailbox::message_ptr msg) -> void;

    private:
        cooperative_actor(supervisor_abstract*, std::string);

        inline inbox_t& inbox() {
            return inbox_;
        }

        bool activate(scheduler::execution_unit*);
        auto reactivate(mailbox::message& x) -> void;
        auto context(scheduler::execution_unit*) -> void;
        auto context() const -> scheduler::execution_unit*;
        auto supervisor() -> supervisor_abstract*;
        auto get_high_priority_queue() -> high_priority_queue&;
        auto get_normal_priority_queue() -> normal_priority_queue&;

        supervisor_abstract* supervisor_;
        scheduler::execution_unit* executor_;
        mailbox::message* current_message_;
        inbox_t inbox_;
    };

    template<class T>
    auto intrusive_ptr_add_ref(T* ptr) -> typename std::enable_if<std::is_same<T*, cooperative_actor*>::value>::type {
        ptr->intrusive_ptr_add_ref_impl();
    }

    template<class T>
    auto intrusive_ptr_release(T* ptr) -> typename std::enable_if<std::is_same<T*, cooperative_actor*>::value>::type {
        ptr->intrusive_ptr_release_impl();
    }

}} // namespace actor_zeta::base
