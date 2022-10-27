#pragma once

#include <actor-zeta/detail/queue/new_round_result.hpp>
#include <actor-zeta/detail/queue/task_queue.hpp>
#include <actor-zeta/detail/queue/task_result.hpp>

namespace actor_zeta { namespace detail {

    /// A Deficit Round Robin queue.
    template <class Policy, typename _Alloc = std::allocator<typename Policy::mapped_type> >
    class queue : public task_queue<Policy, _Alloc> {
    public:
        using super = task_queue<Policy, _Alloc>;
        using typename super::policy_type;
        using typename super::unique_pointer;
        using typename super::value_type;
        using deficit_type = typename policy_type::deficit_type;

        explicit queue(_Alloc* allocator, policy_type policy)
            : super(allocator, std::move(policy))
            , deficit_(0) {}

        queue(queue&& other) noexcept
            : super(std::move(other))
            , deficit_(0) {}

    //    auto operator=(queue&& other) noexcept -> queue& {
    //        super::operator=(std::move(other));
    //        return *this;
    //    }

        auto deficit() const -> deficit_type {
            return deficit_;
        }

        void inc_deficit(deficit_type deficit) noexcept {
            if (!super::empty()) {
                deficit_ += deficit;
            }
        }

        void flush_cache() const noexcept {}

        /// Consumes items from the queue until the queue is empty or there is not
        /// enough deficit to dequeue the next task.
        /// @returns `true` if `func` consumed at least one item.
        template <class F>
        auto consume(F& func) noexcept(noexcept(func(std::declval<value_type&>()))) -> bool {
            auto res = new_round(0, func);
            return res.consumed_items;
        }

        /// Takes the first element out of the queue if the deficit allows it and
        /// returns the element.
        /// @private
        auto next() noexcept -> unique_pointer {
            return super::next(deficit_);
        }

        /// Run a next round with `quantum`, dispatching all tasks to `consumer`.
        /// @returns `true` if at least one item was consumed, `false` otherwise.
        template <class F>
        auto new_round(deficit_type quantum, F& consumer) -> new_round_result {
            size_t consumed = 0;
            if (!super::empty()) {
                deficit_ += quantum;
                auto ptr = next();
                if (ptr == nullptr) {
                    return {0, false};
                }
                do {
                    ++consumed;
                    switch (consumer(*ptr)) {
                        default:
                            break;
                        case task_result::stop:
                            return {consumed, false};
                        case task_result::stop_all:
                            return {consumed, true};
                    }
                    ptr = next();
                } while (ptr != nullptr);
                return {consumed, false};
            }
            return {consumed, false};
        }

    private:
        deficit_type deficit_ = 0;
    };

}} // namespace actor_zeta::detail
