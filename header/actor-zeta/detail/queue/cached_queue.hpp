#pragma once

#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/detail/queue/new_round_result.hpp>
#include <actor-zeta/detail/queue/task_queue.hpp>
#include <actor-zeta/detail/queue/task_result.hpp>

namespace actor_zeta { namespace detail {

    /// A Deficit Round Robin queue with an internal cache for allowing skipping
    /// consumers.
    template<class Policy>
    class cached_queue : protected pmr::memory_resource_base {
    public:
        using policy_type = Policy;
        using value_type = typename policy_type::mapped_type;
        using node_type = typename value_type::node_type;
        using node_pointer = node_type*;
        using pointer = value_type*;
        using unique_pointer = typename policy_type::unique_pointer;
        using deficit_type = typename policy_type::deficit_type;
        using task_size_type = typename policy_type::task_size_type;
        using list_type = task_queue<policy_type>;
        using cache_type = task_queue<policy_type>;

        explicit cached_queue(pmr::memory_resource* memory_resource, policy_type policy)
            : pmr::memory_resource_base(memory_resource)
            , list_(resource(), policy)
            , deficit_(0)
            , cache_(resource(), std::move(policy)) {}

        cached_queue(cached_queue&& other) noexcept
            : pmr::memory_resource_base(other.resource())
            , list_(std::move(other.list_))
            , deficit_(other.deficit_)
            , cache_(std::move(other.cache_)) {}

        auto operator=(cached_queue&& other) noexcept -> cached_queue& {
            ~cached_queue();
            cached_queue(std::move(other));
//            list_ = std::move(other.list_);
//            deficit_ = other.deficit_;
//            cache_ = std::move(other.cache_);
            return *this;
        }

        /// Returns the policy object.
        auto policy() noexcept -> policy_type& {
            return list_.policy();
        }

        /// Returns the policy object.
        auto policy() const noexcept -> const policy_type& {
            return list_.policy();
        }

        auto deficit() const -> deficit_type {
            return deficit_;
        }

        /// Returns the accumulated size of all stored tasks in the list, i.e., tasks
        /// that are not in the cache.
        auto total_task_size() const -> task_size_type {
            return list_.total_task_size();
        }

        /// Returns whether the queue has no uncached tasks.
        auto empty() const noexcept -> bool {
            return total_task_size() == 0;
        }

        /// Peeks at the first element of the list.
        auto peek() noexcept -> pointer {
            return list_.peek();
        }

        /// Applies `func` to each element in the queue, excluding cached elements.
        template<class F>
        void peek_all(F func) const {
            list_.peek_all(func);
        }

        /// Tries to find the next element in the queue (excluding cached elements)
        /// that matches the given predicate.
        template <class Predicate>
        auto find_if(Predicate pred) -> pointer {
            return list_.find_if(pred);
        }

        /// Removes all elements from the queue.
        void clear() {
            list_.clear();
            cache_.clear();
        }

        void inc_deficit(deficit_type deficit) noexcept {
            if (!list_.empty()) {
                deficit_ += deficit;
            }
        }

        void flush_cache() noexcept {
            list_.prepend(cache_);
        }

        /// Takes the first element out of the queue if the deficit allows it and
        /// returns the element.
        /// @private
        auto next() noexcept -> unique_pointer {
            return list_.next(deficit_);
        }

        /// Takes the first element out of the queue (after flushing the cache)  and
        /// returns it, ignoring the deficit count.
        auto take_front() noexcept -> unique_pointer {
            flush_cache();
            if (!list_.empty()) {
                auto dummy_deficit = std::numeric_limits<deficit_type>::max();
                return list_.next(dummy_deficit);
            }
            return {nullptr, pmr::deleter_t(resource())};
        }

        /// Consumes items from the queue until the queue is empty, there is not
        /// enough deficit to dequeue the next task or the consumer returns `stop`.
        /// @returns `true` if `func` consumed at least one item.
        template<class F>
        auto consume(F& func) noexcept(noexcept(func(std::declval<value_type&>()))) -> bool {
            return new_round(0, func).consumed_items > 0;
        }

        /// Run a next round with `quantum`, dispatching all tasks to `consumer`.
        template<class F>
        auto new_round(deficit_type quantum, F& consumer) noexcept(
            noexcept(consumer(std::declval<value_type&>()))) -> new_round_result {
            if (list_.empty()) {
                return {0, false};
            }
            deficit_ += quantum;
            auto ptr = next();
            if (ptr == nullptr) {
                return {0, false};
            }
            size_t consumed = 0;
            do {
                auto consumer_res = consumer(*ptr);
                switch (consumer_res) {
                    case task_result::skip:
                        deficit_ += policy().task_size(*ptr);
                        cache_.push_back(ptr.release());
                        if (list_.empty()) {
                            deficit_ = 0;
                            return {consumed, false};
                        }
                        break;
                    case task_result::resume:
                        ++consumed;
                        flush_cache();
                        if (list_.empty()) {
                            deficit_ = 0;
                            return {consumed, false};
                        }
                        break;
                    default:
                        ++consumed;
                        flush_cache();
                        if (list_.empty())
                            deficit_ = 0;
                        return {consumed, consumer_res == task_result::stop_all};
                }
                ptr = next();
            } while (ptr != nullptr);
            return {consumed, false};
        }

        auto cache() noexcept -> cache_type& {
            return cache_;
        }

        /// Appends `new_element` to the queue.
        /// @pre `new_element != nullptr`
        auto push_back(pointer new_element) noexcept -> bool {
            return list_.push_back(new_element);
        }

        /// Appends `new_element` to the queue.
        /// @pre `new_element != nullptr`
        auto push_back(unique_pointer new_element) noexcept -> bool {
            return push_back(new_element.release());
        }

        /// Creates dynamically allocated element from `elements...` and appends it.
        template<class... args>
        auto emplace_back(args&&... elements) -> bool {
            auto* value = allocate_ptr<value_type>(std::forward<args&&>(elements)...);
            assert(value);
            return push_back(value);
        }

        /// @private
        void lifo_append(node_pointer new_element) {
            list_.lifo_append(new_element);
        }

        /// @private
        void stop_lifo_append() {
            list_.stop_lifo_append();
        }

    private:
        list_type list_;
        deficit_type deficit_ = 0;
        cache_type cache_;
    };

}} // namespace actor_zeta::detail
