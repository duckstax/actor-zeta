#pragma once

#include <actor-zeta/base/abstract_actor.hpp>
#include <actor-zeta/detail/single_reader_queue.hpp>
#include <actor-zeta/executor/executable.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
///
/// @brief Specialization of actor with scheduling functionality
///


        enum invoke_message_result {
            im_success,
            im_skipped,
            im_dropped
        };

        enum class message_category {
            /// Denotes an expired and thus obsolete timeout.
            expired_timeout,
            /// Triggers the currently active timeout.
            timeout,
            /// Triggers the current behavior.
            ordinary,
            /// Triggers handlers for system messages such as `exit_msg` or `down_msg`.
            internal
        };

        /// Result of one-shot activations.
        enum class activation_result {
            /// Actor is still alive and handled the activation message.
            success,
            /// Actor handled the activation message and terminated.
            terminated,
            /// Actor skipped the activation message.
            skipped,
            /// Actor dropped the activation message.
            dropped
        };

        enum class state : int {
            empty = 0x01,
            busy
    };

        class cooperative_actor
                : public abstract_actor
                , public executor::executable
                {
        public:

            using mailbox_t = detail::single_reader_queue<message>;

            using communication_module::enqueue;

            void enqueue(message_ptr, executor::execution_device *) final;

            ///TODO:
            //void launch(executor::execution_device *, bool /*hide*/) final;

            executor::executable_result run(executor::execution_device *, size_t max_throughput) final;

            ~cooperative_actor() override;

        protected:
            cooperative_actor(supervisor &, detail::string_view);

            void intrusive_ptr_add_ref_impl() override;

            void intrusive_ptr_release_impl() override;

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
            void cleanup();

            bool consume_from_cache();

            invoke_message_result consume(message& );


// message processing -----------------------------------------------------

            inline mailbox_t & mailbox() {
                return mailbox_;
            }

            bool activate(executor::execution_device * ctx);
            auto reactivate(message& x) -> activation_result ;

            message_ptr next_message();

            bool has_next_message();

            void push_to_cache(message_ptr ptr);

            auto current_message() -> message* {
                return current_message_;
            }

// ----------------------------------------------------- message processing
            message* current_message_;
            mailbox_t mailbox_;
            std::atomic<int> flags_;
        };
}}
