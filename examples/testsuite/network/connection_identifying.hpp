#pragma once

#include <string>

namespace actor_zeta { namespace network {
    ///
    /// @enum type_connect
    /// @brief
    ///
    enum class connect_type : uint8_t {
        tcp,
        udp
    };
    ///
    /// @brief
    ///
    class connection_identifying {
    public:
        connection_identifying() = default;

        connection_identifying(const connection_identifying&) = default;

        connection_identifying& operator=(const connection_identifying&) = default;

        connection_identifying(connection_identifying&&) = default;

        connection_identifying& operator=(connection_identifying&&) = default;

        connection_identifying(const connect_type& tc, const std::string& ip_, const int& port_);

        std::string to_string() const;

        const std::string& ip() const;

        const int& port() const;

        bool operator==(const connection_identifying& ci) const;

    private:
        connect_type type_connect_;
        std::string ip_;
        int port_;
    };

}
} // namespace actor_zeta::network

namespace std {
    std::string to_string(actor_zeta::network::connect_type);

    std::string to_string(actor_zeta::network::connection_identifying);

    template<>
    struct hash<actor_zeta::network::connection_identifying> {
        inline size_t operator()(const actor_zeta::network::connection_identifying& ref) const {
            return hash<string>{}(ref.to_string());
        }
    };

} // namespace std
