#include <actor-zeta/send.hpp>

namespace actor_zeta {

    void send(base::address_t address, message_ptr msg) {
        address.enqueue(std::move(msg));
    }

} // namespace actor_zeta