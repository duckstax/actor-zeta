#ifndef MULTIPLEXER_HPP
#define MULTIPLEXER_HPP

#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/connection_handler.hpp"

namespace actor_zeta {
    namespace network {
        struct multiplexer {
            virtual int run() = 0;

            virtual ~multiplexer() { };

            virtual void new_tcp_interfaces(const std::string &host, uint16_t port) = 0;

        };

        using unique_multiplexer_ptr = std::unique_ptr<multiplexer>;
    }
}
#endif //MULTIPLEXER_HPP
