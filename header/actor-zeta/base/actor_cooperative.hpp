#pragma once

#include "forwards.hpp"

#include "actor-zeta/detail/ref_counted.hpp"
#include <actor-zeta/detail/single_reader_queue.hpp>

#include <actor-zeta/scheduler/resumable.hpp>
#include <actor-zeta/clock/clock.hpp>
#include <actor-zeta/base/behavior.hpp>
#include <actor-zeta/base/actor_abstract.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Specialization of actor with scheduling functionality
    ///

    class actor_cooperative_t
        : public actor_abstract
        , public ref_counted
        , public scheduler::resumable {
    public:
        using mailbox_t = detail::single_reader_queue<message>;

        scheduler::resume_result resume(scheduler::execution_unit*, max_throughput_t) final;
        ~actor_cooperative_t() override;

        void intrusive_ptr_add_ref_impl() override;
        void intrusive_ptr_release_impl() override;

    protected:
        actor_cooperative_t(supervisor_abstract*, std::string, int64_t);
        void enqueue_impl(message_ptr, scheduler::execution_unit*) final;

        // Non thread-safe method
        auto current_message() -> message*;

        behavior_container behavior_;

    private:
        enum class state : int {
            empty = 0x01,
            busy
        };

        inline int flags() const {
            return flags_.load(std::memory_order_relaxed);
        }

        inline void flags(int new_value) {
            flags_.store(new_value, std::memory_order_relaxed);
        }

        void cleanup();
        bool consume_from_cache();
        void consume(message&);

        // message processing -----------------------------------------------------

        inline mailbox_t& mailbox() {
            return mailbox_;
        }

        bool activate(scheduler::execution_unit* ctx);
        auto reactivate(message& x) -> void;
        message_ptr next_message();
        bool has_next_message();
        void push_to_cache(message_ptr ptr);
        auto context(scheduler::execution_unit*) -> void;
        auto context() const -> scheduler::execution_unit*;
        auto supervisor() -> supervisor_abstract*;

        // ----------------------------------------------------- message processing

        auto clock() noexcept -> clock::clock_t&;
        supervisor_abstract* supervisor_;
        scheduler::execution_unit* executor_;
        message* current_message_;
        mailbox_t mailbox_;
        std::atomic<int> flags_;
    };

    template<class T>
    auto intrusive_ptr_add_ref(T* ptr) -> typename std::enable_if<std::is_same<T*, actor_cooperative_t*>::value>::type {
        ptr->intrusive_ptr_add_ref_impl();
    }

    template<class T>
    auto intrusive_ptr_release(T* ptr) -> typename std::enable_if<std::is_same<T*, actor_cooperative_t*>::value>::type {
        ptr->intrusive_ptr_release_impl();
    }

}} // namespace actor_zeta::base
