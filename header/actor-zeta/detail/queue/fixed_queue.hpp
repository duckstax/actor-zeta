#pragma once

#include "new_round_result.hpp"
#include "task_result.hpp"

namespace actor_zeta { namespace detail {

    /// A work queue that internally multiplexes any number of DRR queues.
    template<class Policy, class Q, class... Qs>
    class fixed_queue {
    public:
        using tuple_type = std::tuple<Q, Qs...>;
        using policy_type = Policy;
        using deficit_type = typename policy_type::deficit_type;
        using value_type = typename policy_type::mapped_type;
        using pointer = value_type*;
        using unique_pointer = typename policy_type::unique_pointer;
        using task_size_type = typename policy_type::task_size_type;

        template<size_t I>
        using index = std::integral_constant<size_t, I>;

        static constexpr size_t num_queues = sizeof...(Qs) + 1;

        fixed_queue(policy_type policy0, typename Q::policy_type policy1, typename Qs::policy_type... policies)
            : qs_(std::move(policy1), std::move(policies)...)
            , policy_(std::move(policy0)) {}

        auto policy() noexcept -> policy_type& {
            return policy_;
        }

        auto policy() const noexcept -> const policy_type& {
            return policy_;
        }

        auto push_back(value_type* new_element) noexcept -> bool {
            return push_back_recursion<0>(policy_.id_of(*new_element), new_element);
        }

        auto push_back(unique_pointer new_element) noexcept -> bool {
            return push_back(new_element.release());
        }

        template<class... Ts>
        auto emplace_back(Ts&&... elements) -> bool {
            return push_back(new value_type(std::forward<Ts>(elements)...));
        }

        void inc_deficit(deficit_type deficit) noexcept {
            inc_deficit_recursion<0>(deficit);
        }

        /// Run a new round with `quantum`, dispatching all tasks to `consumer`.
        /// @returns `true` if at least one item was consumed, `false` otherwise.
        template<class F>
        auto new_round(deficit_type quantum, F& func) -> new_round_result {
            return new_round_recursion<0>(quantum, func);
        }

        auto peek() noexcept -> pointer {
            return peek_recursion<0>();
        }

        /// Tries to find an element in the queue that matches the given predicate.
        template <class Predicate>
        auto find_if(Predicate pred) -> pointer {
            return find_if_recursion<0>(pred);
        }

        /// Applies `func` to each element in the queue.
        template<class F>
        void peek_all(F func) const {
            return peek_all_recursion<0>(func);
        }

        /// Returns `true` if all queues are empty, `false` otherwise.
        auto empty() const noexcept -> bool {
            return total_task_size() == 0;
        }

        void flush_cache() noexcept {
            flush_cache_recursion<0>();
        }

        auto total_task_size() const noexcept -> task_size_type {
            return total_task_size_recursion<0>();
        }

        /// Returns the tuple containing all nested queues.
        auto queues() noexcept -> tuple_type& {
            return qs_;
        }

        /// Returns the tuple containing all nested queues.
        auto queues() const noexcept -> const tuple_type& {
            return qs_;
        }

        void lifo_append(pointer ptr) noexcept {
            lifo_append_recursion<0>(policy_.id_of(*ptr), ptr);
        }

        void stop_lifo_append() noexcept {
            stop_lifo_append_recursion<0>();
        }

    private:
        tuple_type qs_;
        Policy policy_;

        template<size_t I>
        auto push_back_recursion(size_t, value_type*) noexcept -> typename std::enable_if<I == num_queues, bool>::type {
            return false;
        }

        template<size_t I>
        auto push_back_recursion(size_t pos, value_type* ptr) noexcept -> typename std::enable_if<I != num_queues, bool>::type {
            if (pos == I) {
                auto& q = std::get<I>(qs_);
                return q.push_back(ptr);
            }
            return push_back_recursion<I + 1>(pos, ptr);
        }

        template<size_t I, class Queue, class F>
        struct new_round_recursion_helper {
            Queue& q;
            F& f;
            template<class... Ts>
            auto operator()(Ts&&... xs)
                -> decltype((std::declval<F&>()) (std::declval<index<I>>(),
                                                  std::declval<Queue&>(),
                                                  std::forward<Ts>(xs)...)) {
                index<I> id;
                return f(id, q, std::forward<Ts>(xs)...);
            }
        };

        template<size_t I>
        auto inc_deficit_recursion(deficit_type) noexcept -> typename std::enable_if<I == num_queues, void>::type {}

        template<size_t I>
        auto inc_deficit_recursion(deficit_type quantum) noexcept -> typename std::enable_if<I != num_queues, void>::type {
            auto& q = std::get<I>(qs_);
            q.inc_deficit(policy_.quantum(q, quantum));
            inc_deficit_recursion<I + 1>(quantum);
        }

        template<size_t I, class F>
        auto new_round_recursion(deficit_type, F&) noexcept -> typename std::enable_if<I == num_queues, new_round_result>::type {
            return {0, false};
        }

        template<size_t I, class F>
        auto new_round_recursion(deficit_type quantum, F& func) -> typename std::enable_if<I != num_queues, new_round_result>::type {
            auto& q = std::get<I>(qs_);
            using q_type = typename std::decay<decltype(q)>::type;
            new_round_recursion_helper<I, q_type, F> g{q, func};
            auto res = q.new_round(policy_.quantum(q, quantum), g);
            if (res.stop_all) {
                inc_deficit_recursion<I + 1>(quantum);
                return res;
            }
            auto sub = new_round_recursion<I + 1>(quantum, func);
            return {res.consumed_items + sub.consumed_items, sub.stop_all};
        }

        template<size_t I>
        auto peek_recursion() noexcept -> typename std::enable_if<I == num_queues, pointer>::type {
            return nullptr;
        }

        template<size_t I>
        auto peek_recursion() noexcept -> typename std::enable_if<I != num_queues, pointer>::type {
            auto ptr = std::get<I>(qs_).peek();
            if (ptr != nullptr) {
                return ptr;
            }
            return peek_recursion<I + 1>();
        }

        template <size_t I, class Predicate>
        auto find_if_recursion(Predicate) -> typename std::enable_if<I == num_queues, pointer>::type {
            return nullptr;
        }

        template <size_t I, class Predicate>
        auto find_if_recursion(Predicate pred) -> typename std::enable_if<I != num_queues, pointer>::type {
            if (auto ptr = std::get<I>(qs_).find_if(pred)) {
                return ptr;
            }
            return find_if_recursion<I + 1>(std::move(pred));
        }

        template<size_t I, class F>
        auto peek_all_recursion(F&) const -> typename std::enable_if<I == num_queues, void>::type {}

        template<size_t I, class F>
        auto peek_all_recursion(F& func) const -> typename std::enable_if<I != num_queues, void>::type {
            std::get<I>(qs_).peek_all(func);
            peek_all_recursion<I + 1>(func);
        }

        template<size_t I>
        auto flush_cache_recursion() noexcept -> typename std::enable_if<I == num_queues, void>::type {}

        template<size_t I>
        auto flush_cache_recursion() noexcept -> typename std::enable_if<I != num_queues, void>::type {
            std::get<I>(qs_).flush_cache();
            flush_cache_recursion<I + 1>();
        }
        template<size_t I>
        auto total_task_size_recursion() const noexcept -> typename std::enable_if<I == num_queues, task_size_type>::type {
            return 0;
        }

        template<size_t I>
        auto total_task_size_recursion() const noexcept -> typename std::enable_if<I != num_queues, task_size_type>::type {
            return std::get<I>(qs_).total_task_size() + total_task_size_recursion<I + 1>();
        }

        template<size_t I>
        auto lifo_append_recursion(size_t, pointer) noexcept -> typename std::enable_if<I == num_queues, void>::type {}

        template<size_t I>
        auto lifo_append_recursion(size_t i, pointer ptr) noexcept -> typename std::enable_if<I != num_queues, void>::type {
            if (i == I) {
                std::get<I>(qs_).lifo_append(ptr);
            }
            lifo_append_recursion<I + 1>(i, ptr);
        }

        template<size_t I>
        auto stop_lifo_append_recursion() noexcept -> typename std::enable_if<I == num_queues, void>::type {}

        template<size_t I>
        auto stop_lifo_append_recursion() noexcept -> typename std::enable_if<I != num_queues, void>::type {
            std::get<I>(qs_).stop_lifo_append();
            stop_lifo_append_recursion<I + 1>();
        }
    };

}} // namespace actor_zeta::detail
