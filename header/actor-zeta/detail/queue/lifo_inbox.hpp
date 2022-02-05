#pragma once

#include <atomic>
#include <condition_variable>

#include "enqueue_result.hpp"

namespace actor_zeta { namespace detail {

    /// An intrusive, thread-safe LIFO queue implementation for a single reader
    /// with any number of writers.
    template<class Policy>
    class lifo_inbox {
    public:
        using policy_type = Policy;
        using value_type = typename policy_type::mapped_type;
        using pointer = value_type*;
        using node_type = typename value_type::node_type;
        using node_pointer = node_type*;
        using unique_pointer = typename policy_type::unique_pointer;
        using deleter_type = typename unique_pointer::deleter_type;

        /// Casts a node type to its value type.
        static auto promote(node_pointer ptr) noexcept -> pointer {
            return static_cast<pointer>(ptr);
        }

        /// Tries to enqueue a new element to the inbox.
        /// @threadsafe
        auto push_front(pointer new_element) noexcept -> enqueue_result {
            assert(new_element != nullptr);
            pointer last_element = stack_.load();
            auto eof = stack_closed_tag();
            auto blk = reader_blocked_tag();
            while (last_element != eof) {
                new_element->next = last_element != blk ? last_element : nullptr;
                if (stack_.compare_exchange_strong(last_element, new_element))
                    return last_element == reader_blocked_tag()
                               ? enqueue_result::unblocked_reader
                               : enqueue_result::success;
            }
            deleter_type deleter;
            deleter(new_element);
            return enqueue_result::queue_closed;
        }

        /// Tries to enqueue a new element to the inbox.
        /// @threadsafe
        auto push_front(unique_pointer new_element) noexcept -> enqueue_result {
            return push_front(new_element.release());
        }

        /// Tries to enqueue a new element to the mailbox.
        /// @threadsafe
        template<class... Ts>
        auto emplace_front(Ts&&... elements) -> enqueue_result {
            return push_front(new value_type(std::forward<Ts>(elements)...));
        }

        /// Queries whether this queue is empty.
        /// @pre `!closed() && !blocked()`
        auto empty() const noexcept -> bool {
            assert(!closed());
            assert(!blocked());
            return stack_.load() == stack_empty_tag();
        }

        /// Queries whether this has been closed.
        auto closed() const noexcept -> bool {
            return stack_.load() == stack_closed_tag();
        }

        /// Queries whether this has been marked as blocked, i.e.,
        /// the owner of the list is waiting for new data.
        auto blocked() const noexcept -> bool {
            return stack_.load() == reader_blocked_tag();
        }

        /// Tries to set this queue from `empty` to `blocked`.
        auto try_block() noexcept -> bool {
            auto empty_tag = stack_empty_tag();
            return stack_.compare_exchange_strong(empty_tag, reader_blocked_tag());
        }

        /// Tries to set this queue from `blocked` to `empty`.
        auto try_unblock() noexcept -> bool {
            auto blocked_tag = reader_blocked_tag();
            return stack_.compare_exchange_strong(blocked_tag, stack_empty_tag());
        }

        /// Sets the head to `new_head` and returns the previous head if the queue was not empty.
        auto take_head(pointer new_head) noexcept -> pointer {
            assert(new_head == stack_closed_tag() || new_head == stack_empty_tag());
            pointer last_element = stack_.load();
            assert(last_element != stack_closed_tag());
            assert(last_element != reader_blocked_tag() || new_head == stack_closed_tag());
            while (last_element != new_head) {
                if (stack_.compare_exchange_weak(last_element, new_head)) {
                    assert(last_element != stack_closed_tag());
                    if (is_empty_or_blocked_tag(last_element)) {
                        assert(new_head == stack_closed_tag());
                        return nullptr;
                    }
                    return last_element;
                }
            }
            return nullptr;
        }

        /// Sets the head to `stack_empty_tag()` and returns the previous head if
        /// the queue was not empty.
        auto take_head() noexcept -> pointer {
            return take_head(stack_empty_tag());
        }

        /// Closes this queue and deletes all remaining elements.
        /// @warning Call only from the reader (owner).
        void close() noexcept {
            deleter_type deleter;
            close(deleter);
        }

        /// Closes this queue and applies `func` to each pointer. The function object
        /// `func` must take ownership of the passed pointer.
        /// @warning Call only from the reader (owner).
        template<class F>
        void close(F& func) noexcept(noexcept(func(std::declval<pointer>()))) {
            node_pointer ptr = take_head(stack_closed_tag());
            while (ptr != nullptr) {
                auto next = ptr->next;
                func(promote(ptr));
                ptr = next;
            }
        }

        lifo_inbox() noexcept {
            stack_ = stack_empty_tag();
        }

        ~lifo_inbox() noexcept {
            if (!closed()) {
                close();
            }
        }

        template<class Mutex, class CondVar>
        auto synchronized_push_front(Mutex& mtx, CondVar& cond, pointer new_element) -> bool {
            switch (push_front(new_element)) {
                default:
                    return true;
                case enqueue_result::unblocked_reader: {
                    std::unique_lock<Mutex> guard(mtx);
                    cond.notify_one();
                    return true;
                }
                case enqueue_result::queue_closed:
                    return false;
            }
        }

        template<class Mutex, class CondVar>
        auto synchronized_push_front(Mutex& mtx, CondVar& cond, unique_pointer new_element) -> bool {
            return synchronized_push_front(mtx, cond, new_element.release());
        }

        template<class Mutex, class CondVar, class... Ts>
        auto synchronized_emplace_front(Mutex& mtx, CondVar& cond, Ts&&... elements) -> bool {
            return synchronized_push_front(mtx, cond, new value_type(std::forward<Ts>(elements)...));
        }

        template<class Mutex, class CondVar>
        void synchronized_await(Mutex& mtx, CondVar& cond) {
            assert(!closed());
            if (try_block()) {
                std::unique_lock<Mutex> guard(mtx);
                while (blocked()) {
                    cond.wait(guard);
                }
            }
        }

        template<class Mutex, class CondVar, class TimePoint>
        auto synchronized_await(Mutex& mtx, CondVar& cond, const TimePoint& timeout) -> bool {
            assert(!closed());
            if (try_block()) {
                std::unique_lock<Mutex> guard(mtx);
                while (blocked()) {
                    if (cond.wait_until(guard, timeout) == std::cv_status::timeout) {
                        return !try_unblock();
                    }
                }
            }
            return true;
        }

    private:
        static constexpr auto stack_empty_tag() -> pointer {
            return static_cast<pointer>(nullptr);
        }

        auto stack_closed_tag() const noexcept -> pointer {
            return reinterpret_cast<pointer>(reinterpret_cast<intptr_t>(this) + 1);
        }

        auto reader_blocked_tag() const noexcept -> pointer {
            return reinterpret_cast<pointer>(const_cast<lifo_inbox*>(this));
        }

        auto is_empty_or_blocked_tag(pointer x) const noexcept -> bool {
            return x == stack_empty_tag() || x == reader_blocked_tag();
        }

        std::atomic<pointer> stack_;
    };

}} // namespace actor_zeta::detail
