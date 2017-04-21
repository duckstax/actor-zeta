#ifndef MESSAGE_PRIORITIES_HPP
#define MESSAGE_PRIORITIES_HPP

namespace actor_zeta {
    namespace messaging {
///
/// @enum
///
        enum class message_priority : int {
            low = 0,    ///< is coded as std::int of value 0
            normal,     ///< is coded as std::int of value 1
            high        ///< is coded as std::int of value 2
        };
    }
}

#endif //MESSAGE_PRIORITIES_HPP
