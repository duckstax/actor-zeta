#include <cassert>

#include <actor-zeta/base/address_type.hpp>
#include <actor-zeta/messaging/message.hpp>

using actor_zeta::messaging::message;
using actor_zeta::messaging::message;

int main() {

    message msg;

    assert(msg == false);

    message msg_1(address(),"1",int(1));

    assert(msg_1 == true);

    assert(msg_1.command() == "1");

    assert(msg_1.body<int>() == 1 );

    return 0;
}