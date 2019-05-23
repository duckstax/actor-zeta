#pragma once

#include <atomic>
#include <thread>

namespace actor_zeta {

    template<typename Backoff>
    class spin_lock final {
    private:
        std::atomic<bool> spin_;
        std::thread::id owner_id;
    public:

        using backoff_strategy =  Backoff;

        spin_lock() noexcept : owner_id() {
            spin_.store(false, std::memory_order_release);
        }

        explicit spin_lock(bool locked) noexcept : owner_id(locked ? std::this_thread::get_id() : std::thread::id()) {
            spin_.store(locked, std::memory_order_release);
        }

        spin_lock(const spin_lock<Backoff> &) noexcept : spin_(false), owner_id(std::thread::id()) {}

        ~spin_lock() {
            assert(!spin_.load(std::memory_order_relaxed));
        }

        bool is_locked() const noexcept {
            return spin_.load(std::memory_order_relaxed);
        }

        bool try_lock() noexcept {
            bool current = spin_.exchange(true, std::memory_order_acquire);

            ///
            ///if (!bCurrent) {
            ///    owner_id = std::this_thread::get_id();
            ///}

            return !current;
        }

        bool try_lock(unsigned int try_count) noexcept(noexcept(backoff_strategy()())) {
            backoff_strategy back_off;
            while (try_count--) {
                if (try_lock())
                    return true;
                back_off();
            }
            return false;
        }

        void lock() noexcept(noexcept(backoff_strategy()())) {
            backoff_strategy back_off;
            assert(owner_id != std::this_thread::get_id());

            while (!try_lock()) {
                while (spin_.load(std::memory_order_acquire))
                    back_off();
            }

            assert(owner_id == std::this_thread::get_id());
        }

        void unlock() noexcept {
            assert(spin_.load(std::memory_order_relaxed));
            assert(owner_id == std::this_thread::get_id());
            ///(owner_id = std::thread::id() )
            spin_.store(false, std::memory_order_release);
        }
    };

    class exponential final {
    public:
        constexpr exponential() noexcept: exp_cur_(lower_bound) {}

        void operator()() noexcept {
            if (exp_cur_ <= upper_bound) {
                for (std::size_t n = 0; n < exp_cur_; ++n)
                    hint();
                exp_cur_ *= 2;
            } else
                yield();
        }

        void reset() noexcept {
            exp_cur_ = lower_bound;
        }

    private:
        enum : size_t {
            lower_bound = 16,
            upper_bound = 16 * 1024
        };


        size_t exp_cur_;

        void yield() const noexcept {
            std::this_thread::yield();
        }

        void hint() const noexcept {

        }

    };

    using spinlock = spin_lock<exponential>;
}