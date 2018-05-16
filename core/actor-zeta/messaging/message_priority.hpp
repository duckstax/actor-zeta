#ifndef MESSAGE_PRIORITIES_HPP
#define MESSAGE_PRIORITIES_HPP

namespace actor_zeta { namespace messaging {
///
/// @enum
///
        enum class message_priority : uint8_t {
            low = 0,
            normal,
            high
        };

        auto to_string(message_priority) -> std::string;

        auto from_string(const std::string& ) -> message_priority;

    }
}

#endif //MESSAGE_PRIORITIES_HPP
