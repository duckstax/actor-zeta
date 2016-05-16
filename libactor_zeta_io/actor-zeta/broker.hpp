#ifndef ABSTRACT_BROKER_HPP
#define ABSTRACT_BROKER_HPP

#include "actor-zeta/actor/local_actor.hpp"
#include "forwards.hpp"

namespace actor_zeta {
    namespace network {
        class broker : actor_zeta::local_actor {
        public:
            broker();

            multiplexer &backend();

            void set_backend(multiplexer* ptr);

        private:
            std::unique_ptr<multiplexer> backend_;
            std::atomic<size_t> default_max_msg_size{16 * 1024 * 1024};
        };
    }
}
#endif //ABSTRACT_BROKER_HPP
