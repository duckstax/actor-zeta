#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace executor {
///
/// @brief
///
        struct executable {
///
/// @enum 
/// @brief
///
            enum class executable_result {
                resume,     ///< is coded as std::int of value 0
                awaiting,   ///< is coded as std::int of value 1
                done,       ///< is coded as std::int of value 2
                shutdown    ///< is coded as std::int of value 3
            };

            virtual ~executable() = default;

            virtual void attach_to_scheduler() = 0;

            virtual void detach_from_scheduler() = 0;

            virtual executable_result run(executor::execution_device *,size_t max_throughput) = 0;
        };
    }
}
#endif //EXECUTABLE_HPP
