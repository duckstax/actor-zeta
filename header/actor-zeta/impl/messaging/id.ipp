#pragma once

#include <actor-zeta/impl/messaging/id.ipp>

namespace std {

    bool operator==(const actor_zeta::mailbox::message_id& lhs, const actor_zeta::mailbox::message_id& rhs) {
        return lhs.integer_value() == rhs.integer_value();
    }



} // namespace std
