#pragma once

#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/detail/single_reader_queue.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Specialization of actor with scheduling functionality
    ///

    using max_throughput_t = std::size_t;

    class cooperative_actor
        : public actor_abstract
        , public executor::executable {
    public:
        using mailbox_t = detail::single_reader_queue<message>;

        executor::executable_result run(executor::execution_device*, max_throughput_t) final;

        ~cooperative_actor() override;

        void intrusive_ptr_add_ref_impl() override;

        void intrusive_ptr_release_impl() override;

    protected:
        cooperative_actor(supervisor_abstract*, std::string);

        void enqueue_base(message_ptr, executor::execution_device*) final;

        // Non thread-safe method
        auto current_message_impl() -> message* override;

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

        bool activate(executor::execution_device* ctx);

        auto reactivate(message& x) -> void;

        message_ptr next_message();

        bool has_next_message();

        void push_to_cache(message_ptr ptr);

        auto context(executor::execution_device*) -> void;

        auto context() const -> executor::execution_device*;

        auto supervisor() -> supervisor_abstract*;

        // ----------------------------------------------------- message processing
        supervisor_abstract* supervisor_;
        executor::execution_device* executor_;
        message* current_message_;
        mailbox_t mailbox_;
        std::atomic<int> flags_;
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
