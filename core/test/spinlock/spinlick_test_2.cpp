#include <cassert>

#include "actor-zeta/detail/spinlock.hpp"


int main() {

    actor_zeta::spinlock sp;
    actor_zeta::spinlock sp2;

    assert(sp.try_lock());
    assert(!sp.try_lock());
    assert(sp2.try_lock());
    assert(!sp.try_lock());
    assert(!sp2.try_lock());
    sp.unlock();
    sp2.unlock();

    sp.lock();
    assert(!sp.try_lock());
    sp2.lock();
    assert(!sp.try_lock());
    assert(!sp2.try_lock());
    sp.unlock();
    sp2.unlock();

    {
        actor_zeta::spinlock::scoped_lock lock(sp);
        assert(!sp.try_lock());
        actor_zeta::spinlock::scoped_lock lock2(sp2);
        assert(!sp.try_lock());
        assert(!sp2.try_lock());
    }

    return 0;
}