#ifndef CONNECTION_HANDLE_HPP
#define CONNECTION_HANDLE_HPP

#include <string>

namespace actor_zeta {
    namespace network {
///
/// @enum type_connect
/// @brief A strongly typed enum class representing connection type
///
        enum class type_connect : int {
            tcp,    ///< is coded as std::int of value 0
            udp,    ///< is coded as std::int of value 1
        };
///
/// @brief Implementation of connection functionality
///
        class connection_identifying {
        public:
            connection_identifying() = delete;

            connection_identifying(const connection_identifying &) = default;

            connection_identifying &operator=(const connection_identifying &) = default;

            connection_identifying(connection_identifying &&) = default;

            connection_identifying &operator=(connection_identifying &&) = default;

            connection_identifying(const type_connect &tc, const std::string &ip_, const int &port_);

            std::string to_string() const;

            const std::string &ip() const;

            const int &port() const;

            bool operator==(const connection_identifying& ci) const;

        private:
            const type_connect type_connect_;
            const std::string ip_;
            const int port_;
        };

    }
}


namespace std {
    std::string to_string(actor_zeta::network::type_connect);

    std::string to_string(actor_zeta::network::connection_identifying);

    template <>
    struct hash<actor_zeta::network::connection_identifying> {
        inline size_t operator()(const actor_zeta::network::connection_identifying& ref) const {
            return hash<string>{}(ref.to_string());
        }
    };

}
#endif //CONNECTION_HANDLE_HPP
