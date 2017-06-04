#ifndef MULTIPLEXER_HPP
#define MULTIPLEXER_HPP

#include <memory>

#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/network/connection_identifying.hpp"

namespace actor_zeta {
    namespace network {
///
/// @brief
///
        struct multiplexer {
            virtual int run() = 0;

            virtual ~multiplexer() = default;

            virtual void new_tcp_listener(const std::string &host, uint16_t port) = 0;

            virtual void new_tcp_connection(const std::string &host, uint16_t port) = 0;

            virtual void close(const connection_identifying &) = 0;

            virtual void write(const connection_identifying &, const std::string &) = 0;

            virtual void registration_broker_address(const actor::actor_address &) = 0;

        };

        using unique_multiplexer_ptr = std::unique_ptr<multiplexer>;
        using shared_multiplexer_ptr = std::shared_ptr<multiplexer>;
    }
}
#endif //MULTIPLEXER_HPP
