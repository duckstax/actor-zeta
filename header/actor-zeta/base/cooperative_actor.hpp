#pragma once

#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/detail/queue/fifo_inbox.hpp>
#include <actor-zeta/scheduler/resumable.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/mail_box.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Specialization of actor with scheduling functionality
    ///

    class cooperative_actor
        : public actor_abstract
        , public scheduler::resumable {
    public:
        using mailbox_t = detail::fifo_inbox<mailbox_policy>;

        scheduler::resume_result resume(scheduler::execution_unit*, max_throughput_t) final;

        ~cooperative_actor() override;

        void intrusive_ptr_add_ref_impl() override;

        void intrusive_ptr_release_impl() override;

    protected:
        template<class Supervisor>
        cooperative_actor(Supervisor* ptr, std::string type ,int64_t actor_id)
            : cooperative_actor(static_cast<supervisor_abstract*>(ptr),std::move(type),actor_id){};

        bool enqueue_impl(message_ptr, scheduler::execution_unit*) final;

        // Non thread-safe method
        auto current_message_impl() -> message* override;

    private:
        cooperative_actor(supervisor_abstract*, std::string,int64_t);

        void cleanup();

        void consume(message&);

        // message processing -----------------------------------------------------

        inline mailbox_t& mailbox() {
            return mailbox_;
        }

        bool activate(scheduler::execution_unit*);

        auto reactivate(message& x) -> void;

        auto context(scheduler::execution_unit*) -> void;

        auto context() const -> scheduler::execution_unit*;

        auto supervisor() -> supervisor_abstract*;

        auto get_high_priority_queue() -> high_priority_queue&;

        auto get_normal_priority_queue() -> normal_priority_queue&;

        // ----------------------------------------------------- message processing
        supervisor_abstract* supervisor_;
        scheduler::execution_unit* executor_;
        message* current_message_;
        mailbox_t mailbox_;
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
