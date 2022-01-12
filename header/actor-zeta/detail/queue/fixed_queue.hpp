#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

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

        fixed_queue(policy_type p0, typename Q::policy_type p1,
                    typename Qs::policy_type... ps)
            : qs_(std::move(p1), std::move(ps)...)
            , policy_(std::move(p0)) {
            // nop
        }

        policy_type& policy() noexcept {
            return policy_;
        }

        const policy_type& policy() const noexcept {
            return policy_;
        }

        bool push_back(value_type* ptr) noexcept {
            return push_back_recursion<0>(policy_.id_of(*ptr), ptr);
        }

        bool push_back(unique_pointer ptr) noexcept {
            return push_back(ptr.release());
        }

        template<class... Ts>
        bool emplace_back(Ts&&... xs) {
            return push_back(new value_type(std::forward<Ts>(xs)...));
        }

        void inc_deficit(deficit_type x) noexcept {
            inc_deficit_recursion<0>(x);
        }

        /// Run a new round with `quantum`, dispatching all tasks to `consumer`.
        /// @returns `true` if at least one item was consumed, `false` otherwise.
        template<class F>
        new_round_result new_round(deficit_type quantum, F& f) {
            return new_round_recursion<0>(quantum, f);
        }

        pointer peek() noexcept {
            return peek_recursion<0>();
        }

        /// Applies `f` to each element in the queue.
        template<class F>
        void peek_all(F f) const {
            return peek_all_recursion<0>(f);
        }

        /// Returns `true` if all queues are empty, `false` otherwise.
        bool empty() const noexcept {
            return total_task_size() == 0;
        }

        void flush_cache() noexcept {
            flush_cache_recursion<0>();
        }

        task_size_type total_task_size() const noexcept {
            return total_task_size_recursion<0>();
        }

        /// Returns the tuple containing all nested queues.
        tuple_type& queues() noexcept {
            return qs_;
        }

        /// Returns the tuple containing all nested queues.
        const tuple_type& queues() const noexcept {
            return qs_;
        }

        void lifo_append(pointer ptr) noexcept {
            lifo_append_recursion<0>(policy_.id_of(*ptr), ptr);
        }

        void stop_lifo_append() noexcept {
            stop_lifo_append_recursion<0>();
        }

    private:
        // -- recursive helper functions ---------------------------------------------

        // TODO: a lot of this code could be vastly simplified by using C++14 generic
        //       lambdas and simple utility to dispatch on the tuple index. Consider
        //       to revisite this code once we switch to C++14.

        template<size_t I>
        detail::enable_if_t<I == num_queues, bool>
        push_back_recursion(size_t, value_type*) noexcept {
            return false;
        }

        template<size_t I>
        detail::enable_if_t<I != num_queues, bool>
        push_back_recursion(size_t pos, value_type* ptr) noexcept {
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
        detail::enable_if_t<I == num_queues>
        inc_deficit_recursion(deficit_type) noexcept {
            // end of recursion
        }

        template<size_t I>
        detail::enable_if_t<I != num_queues>
        inc_deficit_recursion(deficit_type quantum) noexcept {
            auto& q = std::get<I>(qs_);
            q.inc_deficit(policy_.quantum(q, quantum));
            inc_deficit_recursion<I + 1>(quantum);
        }

        template<size_t I, class F>
        detail::enable_if_t<I == num_queues, new_round_result>
        new_round_recursion(deficit_type, F&) noexcept {
            return {0, false};
        }

        template<size_t I, class F>
        detail::enable_if_t<I != num_queues, new_round_result>
        new_round_recursion(deficit_type quantum, F& f) {
            auto& q = std::get<I>(qs_);
            using q_type = typename std::decay<decltype(q)>::type;
            new_round_recursion_helper<I, q_type, F> g{q, f};
            auto res = q.new_round(policy_.quantum(q, quantum), g);
            if (res.stop_all) {
                // Always increase deficit, even if a previous queue stopped the
                // consumer preemptively.
                inc_deficit_recursion<I + 1>(quantum);
                return res;
            }
            auto sub = new_round_recursion<I + 1>(quantum, f);
            return {res.consumed_items + sub.consumed_items, sub.stop_all};
        }

        template<size_t I>
        detail::enable_if_t<I == num_queues, pointer> peek_recursion() noexcept {
            return nullptr;
        }

        template<size_t I>
        detail::enable_if_t<I != num_queues, pointer> peek_recursion() noexcept {
            auto ptr = std::get<I>(qs_).peek();
            if (ptr != nullptr)
                return ptr;
            return peek_recursion<I + 1>();
        }

        template<size_t I, class F>
        detail::enable_if_t<I == num_queues> peek_all_recursion(F&) const {
            // nop
        }

        template<size_t I, class F>
        detail::enable_if_t<I != num_queues> peek_all_recursion(F& f) const {
            std::get<I>(qs_).peek_all(f);
            peek_all_recursion<I + 1>(f);
        }

        template<size_t I>
        detail::enable_if_t<I == num_queues> flush_cache_recursion() noexcept {
            // nop
        }

        template<size_t I>
        detail::enable_if_t<I != num_queues> flush_cache_recursion() noexcept {
            std::get<I>(qs_).flush_cache();
            flush_cache_recursion<I + 1>();
        }
        template<size_t I>
        detail::enable_if_t<I == num_queues, task_size_type>
        total_task_size_recursion() const noexcept {
            return 0;
        }

        template<size_t I>
        detail::enable_if_t<I != num_queues, task_size_type>
        total_task_size_recursion() const noexcept {
            return std::get<I>(qs_).total_task_size() + total_task_size_recursion<I + 1>();
        }

        template<size_t I>
        detail::enable_if_t<I == num_queues>
        lifo_append_recursion(size_t, pointer) noexcept {
            // nop
        }

        template<size_t I>
        detail::enable_if_t<I != num_queues>
        lifo_append_recursion(size_t i, pointer ptr) noexcept {
            if (i == I)
                std::get<I>(qs_).lifo_append(ptr);
            else
                lifo_append_recursion<I + 1>(i, ptr);
        }

        template<size_t I>
        detail::enable_if_t<I == num_queues> stop_lifo_append_recursion() noexcept {
            // nop
        }

        template<size_t I>
        detail::enable_if_t<I != num_queues> stop_lifo_append_recursion() noexcept {
            std::get<I>(qs_).stop_lifo_append();
            stop_lifo_append_recursion<I + 1>();
        }

        // -- member variables -------------------------------------------------------

        /// All queues.
        tuple_type qs_;

        /// Policy object for adjusting a quantum based on queue weight etc.
        Policy policy_;
    };

}} // namespace actor_zeta::detail
