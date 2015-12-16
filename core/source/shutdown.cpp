#include "shutdown.hpp"
#include <thread>
#include "executor/abstract_coordinator.hpp"

namespace actor_model {

    void shutdown(abstract_coordinator *ac) {
        //ac->shutdown();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
