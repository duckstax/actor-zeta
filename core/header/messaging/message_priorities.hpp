#ifndef MESSAGE_PRIORITIES_HPP
#define MESSAGE_PRIORITIES_HPP

namespace actor_model {
    namespace messaging {
        enum class message_priorities : uint32_t {
            low,
            normal,
            high
        };
    }
}

#endif //MESSAGE_PRIORITIES_HPP
