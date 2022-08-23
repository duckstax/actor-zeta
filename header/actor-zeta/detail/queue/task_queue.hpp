#pragma once

#include <actor-zeta/detail/queue/forward_iterator.hpp>

namespace actor_zeta { namespace detail {

    /// A singly-linked FIFO queue for storing tasks of varying size. This queue is
    /// used as a base type for concrete task abstractions such as `drr_queue` and
    /// therefore has no dequeue functions.
    template<class Policy>
    class task_queue {
    public:
        using policy_type = Policy;
        using value_type = typename policy_type::mapped_type;
        using node_type = typename value_type::node_type;
        using node_pointer = node_type*;
        using pointer = value_type*;
        using unique_pointer = typename policy_type::unique_pointer;
        using task_size_type = typename policy_type::task_size_type;
        using iterator = forward_iterator<value_type>;
        using const_iterator = forward_iterator<const value_type>;

        static auto promote(node_pointer ptr) noexcept -> pointer {
            return static_cast<pointer>(ptr);
        }

        explicit task_queue(policy_type policy)
            : old_last_(nullptr)
            , new_head_(nullptr)
            , policy_(std::move(policy)) {
            init();
        }

        task_queue(task_queue&& other) noexcept
            : task_queue(other.policy()) {
            if (other.empty()) {
                init();
            } else {
                head_.next = other.head_.next;
                tail_.next = other.tail_.next;
                tail_.next->next = &tail_;
                total_task_size_ = other.total_task_size_;
                other.init();
            }
        }

        auto operator=(task_queue&& other) noexcept -> task_queue& {
            deinit();
            if (other.empty()) {
                init();
            } else {
                head_.next = other.head_.next;
                tail_.next = other.tail_.next;
                tail_.next->next = &tail_;
                total_task_size_ = other.total_task_size_;
                other.init();
            }
            return *this;
        }

        virtual ~task_queue() {
            deinit();
        }

        /// Returns the policy object.
        auto policy() noexcept -> policy_type& {
            return policy_;
        }

        /// Returns the policy object.
        auto policy() const noexcept -> const policy_type& {
            return policy_;
        }

        /// Returns the accumulated size of all stored tasks.
        auto total_task_size() const noexcept -> task_size_type {
            return total_task_size_;
        }

        /// Returns whether the queue has no elements.
        auto empty() const noexcept -> bool {
            return total_task_size() == 0;
        }

        /// Peeks at the first element in the queue. Returns `nullptr` if the queue is empty.
        auto peek() noexcept -> pointer {
            auto ptr = head_.next;
            return ptr != &tail_ ? promote(ptr) : nullptr;
        }

        /// Applies `func` to each element in the queue.
        template<class F>
        void peek_all(F func) const {
            for (auto i = begin(); i != end(); ++i) {
                func(*i);
            }
        }

        /// Tries to find the next element in the queue (excluding cached elements)
        /// that matches the given predicate.
        template <class Predicate>
        auto find_if(Predicate pred) -> pointer {
            for (auto i = begin(); i != end(); ++i) {
                if (pred(*i)) {
                    return promote(i.ptr);
                }
            }
            return nullptr;
        }

        /// Removes all elements from the queue.
        void clear() {
            deinit();
            init();
        }

        /// @private
        void inc_total_task_size(task_size_type x) noexcept {
            assert(x > 0);
            total_task_size_ += x;
        }

        /// @private
        void inc_total_task_size(const value_type& x) noexcept {
            inc_total_task_size(policy_.task_size(x));
        }

        /// @private
        void dec_total_task_size(task_size_type x) noexcept {
            assert(x > 0);
            total_task_size_ -= x;
        }

        /// @private
        void dec_total_task_size(const value_type& x) noexcept {
            dec_total_task_size(policy_.task_size(x));
        }

        /// @private
        auto next(task_size_type& deficit) noexcept -> unique_pointer {
            unique_pointer result;
            if (!empty()) {
                auto ptr = promote(head_.next);
                auto size = policy_.task_size(*ptr);
                assert(size > 0);
                if (size <= deficit) {
                    deficit -= size;
                    total_task_size_ -= size;
                    head_.next = ptr->next;
                    if (total_task_size_ == 0) {
                        assert(head_.next == &(tail_));
                        deficit = 0;
                        tail_.next = &(head_);
                    }
                    result.reset(ptr);
                }
            }
            return result;
        }

        /// Returns an iterator to the dummy before the first element.
        auto begin() noexcept -> iterator {
            return head_.next;
        }

        /// Returns an iterator to the dummy before the first element.
        auto begin() const noexcept -> const_iterator {
            return head_.next;
        }

        /// Returns a pointer to the dummy past the last element.
        auto end() noexcept -> iterator {
            return &tail_;
        }

        /// Returns a pointer to the dummy past the last element.
        auto end() const noexcept -> const_iterator {
            return &tail_;
        }

        /// Returns a pointer to the first element.
        auto front() noexcept -> pointer {
            return promote(head_.next);
        }

        /// Returns a pointer to the last element.
        auto back() noexcept -> pointer {
            assert(head_.next != &tail_);
            return promote(tail_.next);
        }

        /// Appends `new_element` to the queue.
        /// @pre `new_element != nullptr`
        auto push_back(pointer new_element) noexcept -> bool {
            assert(new_element != nullptr);
            tail_.next->next = new_element;
            tail_.next = new_element;
            new_element->next = &tail_;
            inc_total_task_size(*new_element);
            return true;
        }

        /// Appends `new_element` to the queue.
        /// @pre `new_element != nullptr`
        auto push_back(unique_pointer new_element) noexcept -> bool {
            return push_back(new_element.release());
        }

        /// Creates a new element from `elements...` and appends it.
        template<class... Ts>
        auto emplace_back(Ts&&... elements) -> bool {
            return push_back(new value_type(std::forward<Ts>(elements)...));
        }

        /// Transfers all element from `other` to the front of this queue.
        template<class Container>
        void prepend(Container& other) {
            if (other.empty()) {
                return;
            }
            if (empty()) {
                *this = std::move(other);
                return;
            }
            other.back()->next = head_.next;
            head_.next = other.front();
            inc_total_task_size(other.total_task_size());
            other.init();
        }

        /// Transfers all element from `other` to the back of this queue.
        template<class Container>
        void append(Container& other) {
            if (other.empty()) {
                return;
            }
            if (empty()) {
                *this = std::move(other);
                return;
            }
            back()->next = other.front();
            other.back()->next = &tail_;
            tail_.next = other.back();
            inc_total_task_size(other.total_task_size());
            other.init();
        }

        /// Allows to insert a LIFO-ordered sequence at the end of the queue by
        /// calling this member function multiple times. Converts the order to FIFO
        /// on the fly.
        /// @warning leaves the queue in an invalid state until calling
        ///          `stop_lifo_append`.
        /// @private
        void lifo_append(node_pointer ptr) {
            if (old_last_ == nullptr) {
                old_last_ = tail_.next;
                push_back(promote(ptr));
            } else {
                ptr->next = new_head_;
                inc_total_task_size(*promote(ptr));
            }
            new_head_ = ptr;
        }

        /// Restores a consistent state of the queue after calling `lifo_append`.
        /// @private
        void stop_lifo_append() {
            if (old_last_ != nullptr) {
                assert(new_head_ != nullptr);
                old_last_->next = new_head_;
                old_last_ = nullptr;
            }
        }

        /// Restores a consistent, empty state.
        /// @private
        void init() noexcept {
            head_.next = &tail_;
            tail_.next = &head_;
            total_task_size_ = 0;
        }

        /// Deletes all elements.
        /// @warning leaves the queue in an invalid state until calling `init` again.
        /// @private
        void deinit() noexcept {
            for (auto i = head_.next; i != &tail_;) {
                auto ptr = i;
                i = i->next;
                typename unique_pointer::deleter_type deleter;
                deleter(promote(ptr));
            }
        }

    protected:
        node_type head_;
        node_type tail_;
        task_size_type total_task_size_;
        node_pointer old_last_;
        node_pointer new_head_;
        policy_type policy_;
    };

}} // namespace actor_zeta::detail
