#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace executor {
///
/// @brief
///

///
/// @enum
/// @brief
///
        enum class executable_result : uint8_t {
            resume,
            awaiting,
            done,
            shutdown
        };


        struct executable {
            virtual ~executable() = default;

            virtual void attach_to_scheduler() = 0;

            virtual void detach_from_scheduler() = 0;

            virtual executable_result run(executor::execution_device *,size_t max_throughput) = 0;
        };
    }
}
#endif //EXECUTABLE_HPP
