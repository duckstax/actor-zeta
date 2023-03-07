#pragma once

#include <memory>
#include <thread>
#include <algorithm>

#include <actor-zeta/detail/ring_buffer.hpp>
#include <actor-zeta/clock/clock.hpp>

namespace actor_zeta { namespace clock {

    template<class actor_traits>
    class thread_safe_clock_t final : public clock_t {
        template<class T>
        using vector_type = typename actor_traits::template vector_type<T>;

    public:
        static constexpr size_t buffer_size = 64;

        struct schedule_entry final {
            bool done;
            time_point t;
            handler f;
            duration_type period;
        };

        using schedule_entry_ptr = typename actor_traits::template unique_ptr_type<schedule_entry>;

        thread_safe_clock_t(detail::pmr::memory_resource*);
        void start_dispatch_loop();
        void stop_dispatch_loop();

    private:
        void schedule_periodically(time_point, handler, duration_type) override;
        void run();
        detail::ring_buffer<schedule_entry_ptr, buffer_size> queue_;
        std::thread dispatcher_;
        std::atomic_bool running_{true};
        vector_type<schedule_entry_ptr> tbl_;
    };

    template<class actor_traits>
    thread_safe_clock_t<actor_traits>::thread_safe_clock_t(detail::pmr::memory_resource* memory_resource)
        : clock_t(memory_resource)
        , tbl_(resource()) {
        tbl_.reserve(buffer_size * 2);
    }

    template<class actor_traits>
    void thread_safe_clock_t<actor_traits>::schedule_periodically(time_point first_run, handler f,duration_type period) {
        auto rawptr = actor_zeta::detail::pmr::allocate_ptr<schedule_entry>(
            resource(),
            false, first_run, std::move(f), period);
        queue_.emplace_back({rawptr, typename actor_traits::template deleter_type<schedule_entry>(resource())});
    }

    template<class actor_traits>
    void thread_safe_clock_t<actor_traits>::run() {
        auto is_done = [](const schedule_entry_ptr& entry) -> bool {
            if (entry) {
                return entry->done;
            }

            return true;
        };
        auto by_timeout = [](const schedule_entry_ptr& x, const schedule_entry_ptr& y) -> bool { return x->t < y->t; };
        while (running_) {
            if (tbl_.empty()) {
                queue_.wait_non_empty();
                queue_.get_all(std::back_inserter(tbl_));
                std::sort(tbl_.begin(), tbl_.end(), by_timeout);
            } else {
                auto next_timeout = (*tbl_.begin())->t;
                if (queue_.wait_non_empty(next_timeout)) {
                    queue_.get_all(std::back_inserter(tbl_));
                    std::sort(tbl_.begin(), tbl_.end(), by_timeout);
                }
            }
            auto n = now();
            for (auto i = tbl_.begin(); i != tbl_.end() && (*i)->t <= n; ++i) {
                auto& entry = **i;
                entry.f();
                if (entry.period.count() > 0) {
                    auto next = entry.t + entry.period;
                    while (next <= n) {
                        next += entry.period;
                    }
                    entry.t = next;
                } else {
                    entry.done = true; // Remove from tbl_ after the for-loop body.
                    ///i->reset();
                }
            }
            tbl_.erase(std::remove_if(tbl_.begin(), tbl_.end(), is_done), tbl_.end());
        }
    }

    template<class actor_traits>
    void thread_safe_clock_t<actor_traits>::start_dispatch_loop() {
        dispatcher_ = detail::launch_thread("clock", [this] { run(); });
    }

    template<class actor_traits>
    void thread_safe_clock_t<actor_traits>::stop_dispatch_loop() {
        schedule(handler(resource(), [this]() { running_ = false; }));
        dispatcher_.join();
    }

}} // namespace actor_zeta::clock
