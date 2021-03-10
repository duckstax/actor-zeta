#pragma once

#include <actor-zeta/base/abstract_actor.hpp>
#include <actor-zeta/detail/single_reader_queue.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Specialization of actor with scheduling functionality
    ///

    using max_throughput_t = std::size_t;

    class cooperative_actor
        : public abstract_actor
        , public executor::executable {
    public:
        using mailbox_t = detail::single_reader_queue<message>;

        executor::executable_result run(executor::execution_device*, max_throughput_t) final;

        ~cooperative_actor() override;

        void intrusive_ptr_add_ref_impl() override;

        void intrusive_ptr_release_impl() override;

    protected:
        cooperative_actor(supervisor_t*, detail::string_view);

        void enqueue_base(message_ptr, executor::execution_device*) final;

        inline void setf(int flag) {
            auto x = flags();
            flags(x | flag);
        }

        inline void unsetf(int flag) {
            auto x = flags();
            flags(x & ~flag);
        }

        inline bool getf(int flag) const {
            return (flags() & flag) != 0;
        }

        inline int flags() const {
            return flags_.load(std::memory_order_relaxed);
        }

        inline void flags(int new_value) {
            flags_.store(new_value, std::memory_order_relaxed);
        }

    private:
        enum class state : int {
            empty = 0x01,
            busy
        };

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

        auto current_message() -> message*;

        auto context(executor::execution_device*) -> void;

        auto context() const -> executor::execution_device*;

        auto supervisor() -> supervisor_t*;

        // ----------------------------------------------------- message processing
        supervisor_t* supervisor_;
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
