#pragma once

#include <actor-zeta/base/behavior.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/queue/fifo_inbox.hpp>
#include <actor-zeta/mailbox.hpp>
#include <actor-zeta/scheduler/resumable.hpp>
#include <actor-zeta/mailbox/message.hpp>

namespace actor_zeta { namespace base {

    /**
     * @class cooperative_actor
     * @brief Specialization of actor with scheduling functionality
     *
     * @tparam actor_traits
     */
    template<typename actor_traits>
    class cooperative_actor
        : public actor_abstract
        , public scheduler::resumable
        , public intrusive_behavior_t<actor_traits> {
        using string_type = typename actor_traits::string_type;

    public:
        using inbox_t = detail::fifo_inbox<mailbox_policy>;
        using supervisor_ptr = supervisor_abstract<actor_traits>*;

        /**
         * @brief resume
         *
         * @return scheduler::resume_result
         */
        scheduler::resume_result resume(scheduler::execution_unit*, max_throughput_t) final;

        ~cooperative_actor() override {}

        void intrusive_ptr_add_ref_impl() override { ref(); }
        void intrusive_ptr_release_impl() override { deref(); }

    protected:
        template<class Supervisor>
        cooperative_actor(Supervisor* ptr, string_type type)
            : cooperative_actor<actor_traits>(static_cast<supervisor_ptr>(ptr), std::move(type)) {};

        void enqueue_impl(mailbox::message_ptr, scheduler::execution_unit*);

        inline auto current_message() -> mailbox::message* {
            return current_message_;
        }
        inline auto set_current_message(mailbox::message_ptr msg) -> void {
            current_message_ = msg.release();
        }

    private:
        cooperative_actor(supervisor_ptr, string_type);

        inline inbox_t& inbox() {
            return inbox_;
        }

        bool activate(scheduler::execution_unit*);
        auto reactivate(mailbox::message& x) -> void;
        inline auto context(scheduler::execution_unit* e) -> void {
            if (e != nullptr) { executor_ = e; }
        }
        inline auto context() const -> scheduler::execution_unit* {
            return executor_;
        }
        inline auto supervisor() -> supervisor_ptr {
            return supervisor_;
        }
        inline auto get_high_priority_queue() -> high_priority_queue& {
            return std::get<high_priority_queue_index>(inbox().queue().queues());
        }
        inline auto get_normal_priority_queue() -> normal_priority_queue& {
            return std::get<normal_priority_queue_index>(inbox().queue().queues());
        }

        supervisor_ptr supervisor_;
        scheduler::execution_unit* executor_;
        mailbox::message* current_message_;
        inbox_t inbox_;
    };

    /**
     * @brief
     *
     * @tparam actor_traits
     * @tparam T
     * @param ptr
     * @return std::enable_if<std::is_same<T*, cooperative_actor<actor_traits>*>::value>::type
     */
    template<typename actor_traits, class T>
    auto intrusive_ptr_add_ref(T* ptr) -> typename std::enable_if<std::is_same<T*, cooperative_actor<actor_traits>*>::value>::type {
        ptr->intrusive_ptr_add_ref_impl();
    }

    /**
     * @brief
     *
     * @tparam actor_traits
     * @tparam T
     * @param ptr
     * @return std::enable_if<std::is_same<T*, cooperative_actor<actor_traits>*>::value>::type
     */
    template<typename actor_traits, class T>
    auto intrusive_ptr_release(T* ptr) -> typename std::enable_if<std::is_same<T*, cooperative_actor<actor_traits>*>::value>::type {
        ptr->intrusive_ptr_release_impl();
    }

    /**
     * @brief
     *
     * @tparam actor_traits
     * @param e
     * @param max_throughput
     * @return scheduler::resume_result
     */
    template<typename actor_traits>
    scheduler::resume_result cooperative_actor<actor_traits>::resume(scheduler::execution_unit* e, size_t max_throughput) {
        if (!activate(e)) {
            return scheduler::resume_result::done;
        }
        static constexpr size_t quantum = 3;
        size_t handled_msgs = 0;

        auto handle_async = [this, max_throughput, &handled_msgs](mailbox::message& x) -> detail::task_result {
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

    /**
     * @brief
     *
     * @tparam actor_traits
     * @param msg
     * @param e
     */
    template<typename actor_traits>
    void cooperative_actor<actor_traits>::enqueue_impl(mailbox::message_ptr msg, scheduler::execution_unit* e) {
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

    /**
     * @brief Construct a new cooperative actor<actor traits>::cooperative actor object
     *
     * @tparam actor_traits
     * @param supervisor
     * @param type
     */
    template<typename actor_traits>
    cooperative_actor<actor_traits>::cooperative_actor(supervisor_ptr supervisor, string_type type)
        : actor_abstract(
//#ifdef DEBUG
//            std::move(type)
//#endif
        )
        , intrusive_behavior_t<actor_traits>(supervisor->resource())
        , supervisor_(supervisor)
        , inbox_(intrusive_behavior_t<actor_traits>::resource(),
            mailbox::priority_message(),
            high_priority_queue(intrusive_behavior_t<actor_traits>::resource(), mailbox::high_priority_message()),
            normal_priority_queue(intrusive_behavior_t<actor_traits>::resource(), mailbox::normal_priority_message())) {
        inbox().try_block(); //todo: bug
    }

    /**
     * @brief
     *
     * @tparam actor_traits
     * @param ctx
     * @return true
     * @return false
     */
    template<typename actor_traits>
    bool cooperative_actor<actor_traits>::activate(scheduler::execution_unit* ctx) {
        //assert(ctx != nullptr);
        if (ctx) {
            context(ctx);
        }
        return true;
    }

    /**
     * @brief
     *
     * @tparam actor_traits
     * @param x
     */
    template<typename actor_traits>
    auto cooperative_actor<actor_traits>::reactivate(mailbox::message& x) -> void {
        current_message_ = &x;
        intrusive_behavior_t<actor_traits>::execute(this, current_message());
    }

}} // namespace actor_zeta::base
