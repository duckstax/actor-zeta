
#include "actor-zeta/detail/spinlock.hpp"

int main(){

    actor_zeta::spinlock sp;
    actor_zeta::spinlock sp2;

    sp.lock();
    sp2.lock();
    sp.unlock();
    sp2.unlock();
    
    return 0;
}