#ifndef MESSAGE_PRIORITIES_HPP
#define MESSAGE_PRIORITIES_HPP

namespace actor_zeta {
    namespace messaging {
        enum class message_priorities {
            low = 0,
            normal,
            high
        };
    }
}

#endif //MESSAGE_PRIORITIES_HPP
