
#include "actor-zeta/detail/spinlock.hpp"

int main(){

    actor_zeta::spinlock sp;
    actor_zeta::spinlock sp2;

    sp.lock();
    sp2.lock();
    sp.unlock();
    sp2.unlock();

    {
        actor_zeta::spinlock::scoped_lock lock( sp );
        actor_zeta::spinlock::scoped_lock lock2( sp2 );
    }

    return 0;
}