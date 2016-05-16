#ifndef MULTIPLEXER_HPP
#define MULTIPLEXER_HPP

#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/connection.hpp"

namespace actor_zeta {
    namespace network {
        class multiplexer {
        public:
            virtual int run() = 0;

            virtual ~multiplexer() { };

            virtual void new_tcp_interfaces(const std::string &host, uint16_t port) = 0;

            virtual void set_notify_interfaces(proxy_handler&&) = 0;
        };

        using unique_multiplexer_ptr = std::unique_ptr<multiplexer>;
    }
}
#endif //MULTIPLEXER_HPP
