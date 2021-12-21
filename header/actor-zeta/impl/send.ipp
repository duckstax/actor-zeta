#pragma once

#include <actor-zeta/send.hpp>

namespace actor_zeta {

    void send(base::address_t address, base::message_ptr msg) {
        address.enqueue(std::move(msg));
    }

} // namespace actor_zeta