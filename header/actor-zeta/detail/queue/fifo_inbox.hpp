#pragma once

#include <actor-zeta/detail/queue/enqueue_result.hpp>
#include <actor-zeta/detail/queue/lifo_inbox.hpp>
#include <actor-zeta/detail/queue/new_round_result.hpp>

namespace actor_zeta { namespace detail {
    /// A FIFO inbox that combines an efficient thread-safe LIFO inbox with a FIFO
    /// queue for re-ordering incoming messages.
    template<class Policy>
    class fifo_inbox {
    public:
        using policy_type = Policy;
        using queue_type = typename policy_type::queue_type;
        using deficit_type = typename policy_type::deficit_type;
        using value_type = typename policy_type::mapped_type;
        using lifo_inbox_type = lifo_inbox<policy_type>;
        using pointer = value_type*;
        using unique_pointer = typename queue_type::unique_pointer;
        using node_pointer = typename value_type::node_pointer;

        template<class... Ts>
        explicit fifo_inbox(Ts&&... xs)
            : queue_(std::forward<Ts&&>(xs)...) {}

        /// Returns an approximation of the current size.
        auto size() noexcept -> size_t {
            fetch_more();
            return queue_.total_task_size();
        }

        /// Queries whether the inbox is empty.
        auto empty() const noexcept -> bool {
            return queue_.empty() && inbox_.empty();
        }

        /// Queries whether this inbox is closed.
        auto closed() const noexcept -> bool {
            return inbox_.closed();
        }

        /// Queries whether this has been marked as blocked, i.e.,
        /// the owner of the list is waiting for new data.
        auto blocked() const noexcept -> bool {
            return inbox_.blocked();
        }

        /// Appends `new_element` to the inbox.
        auto push_back(pointer new_element) noexcept -> enqueue_result {
            return inbox_.push_front(new_element);
        }

        /// Appends `new_element` to the inbox.
        auto push_back(unique_pointer new_element) noexcept -> enqueue_result {
            return push_back(new_element.release());
        }

        template<class... Ts>
        auto emplace_back(Ts&&... elements) -> enqueue_result {
            return push_back(new value_type(std::forward<Ts&&>(elements)...));
        }

        /// @cond PRIVATE

        auto enqueue(pointer ptr) noexcept -> enqueue_result {
            return static_cast<enqueue_result>(inbox_.push_front(ptr));
        }

        auto count() noexcept -> size_t {
            return size();
        }

        auto count(size_t) noexcept -> size_t {
            return size();
        }

        /// @endcond

        void flush_cache() noexcept {
            queue_.flush_cache();
        }

        /// Tries to get more items from the inbox.
        auto fetch_more() -> bool {
            node_pointer head = inbox_.take_head();
            if (head == nullptr) {
                return false;
            }
            do {
                auto next = head->next;
                queue_.lifo_append(lifo_inbox_type::promote(head));
                head = next;
            } while (head != nullptr);
            queue_.stop_lifo_append();
            return true;
        }

        /// Tries to set this queue from `empty` to `blocked`.
        auto try_block() -> bool {
            return queue_.empty() && inbox_.try_block();
        }

        /// Tries to set this queue from `blocked` to `empty`.
        auto try_unblock() -> bool {
            return inbox_.try_unblock();
        }

        /// Closes this inbox and moves all elements to the queue.
        /// @warning Call only from the reader (owner).
        void close() {
            auto f = [&](pointer x) { queue_.lifo_append(x); };
            inbox_.close(f);
            queue_.stop_lifo_append();
        }

        /// Run a new round with `quantum`, dispatching all tasks to `consumer`.
        template<class F>
        auto new_round(deficit_type quantum, F& consumer) -> new_round_result {
            fetch_more();
            return queue_.new_round(quantum, consumer);
        }

        auto peek() noexcept -> pointer {
            fetch_more();
            return queue_.peek();
        }

        /// Tries to find an element in the queue that matches the given predicate.
        template <class Predicate>
        auto find_if(Predicate pred) -> pointer {
            fetch_more();
            return queue_.find_if(pred);
        }

        auto queue() noexcept -> queue_type& {
            return queue_;
        }

    private:
        lifo_inbox_type inbox_;
        queue_type queue_;
    };
}
} // namespace actor_zeta::detail
