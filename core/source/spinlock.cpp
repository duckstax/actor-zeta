#include <actor-zeta/detail/spinlock.hpp>

namespace actor_zeta {

    bool spinlock::try_lock() {
        return !v_.test_and_set(std::memory_order_acquire);
    }

    void spinlock::lock() {
        for (unsigned k = 0; !try_lock(); ++k) {
            yield(k);
        }
    }

    void spinlock::unlock() {
        v_.clear(std::memory_order_release);
    }

    spinlock::scoped_lock::scoped_lock(spinlock &sp) : sp_(sp) {
        sp.lock();
    }

    spinlock::scoped_lock::~scoped_lock() {
        sp_.unlock();
    }
}