#include "actor-zeta/broker.hpp"

namespace actor_zeta {
    namespace network {
        void broker::set_backend(multiplexer *ptr) {
            backend_.reset(ptr);
        }

        multiplexer &broker::backend() {
            return *backend_.get();
        }

        broker::broker(const std::string &name, std::function<behavior (local_actor*)>actions) : local_actor(name, actions, nullptr) {
            init();
        }

        broker::broker(const std::string &name) : local_actor(name, nullptr) {
        }
    }
}
