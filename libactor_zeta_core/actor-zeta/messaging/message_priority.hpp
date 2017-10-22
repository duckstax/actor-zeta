#ifndef MESSAGE_PRIORITIES_HPP
#define MESSAGE_PRIORITIES_HPP

namespace actor_zeta {
    namespace messaging {
///
/// @enum
///
        enum class message_priority : uint8_t {
            low = 0,
            normal,
            high
        };
    }
}

#endif //MESSAGE_PRIORITIES_HPP
