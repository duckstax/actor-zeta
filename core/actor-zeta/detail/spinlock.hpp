#pragma once

#include <atomic>

namespace actor_zeta {

    inline void yield(unsigned /*k*/) {

    }


    /// std::mutex-compatible spinlock class
    class spinlock final {
    private:
        std::atomic_flag v_ = ATOMIC_FLAG_INIT;

    public:

        spinlock() = default;

        spinlock(const spinlock &) = delete;

        spinlock &operator=(const spinlock &) = delete;

        ~spinlock() = default;

        bool try_lock();

        void lock();

        void unlock();

/*
        using native_handle_type = spinlock ;

        native_handle_type native_handle() {
            return v_;
        }
*/
        class scoped_lock final {
        public:

            spinlock &sp_;

            scoped_lock(scoped_lock const &) = delete;

            scoped_lock &operator=(scoped_lock const &) = delete;


            explicit scoped_lock(spinlock &sp);

            ~scoped_lock();
        };

    };
}