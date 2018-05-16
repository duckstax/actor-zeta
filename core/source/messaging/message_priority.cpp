#include <actor-zeta/messaging/message_priority.hpp>

namespace actor_zeta { namespace messaging {


        auto to_string(message_priority priority) -> basic_string<char> {
            switch (priority) {

                case message_priority::low:
                    return std::string("low");
                case message_priority::normal:
                    return std::string("normal");
                case message_priority::high:
                    return std::string("high");
            }
        }


        auto from_string(const std::string &) -> message_priority {

        }

    }
}
