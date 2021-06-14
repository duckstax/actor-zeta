#include <testsuite/network/connection_identifying.hpp>

namespace actor_zeta {
namespace network {

    connection_identifying::connection_identifying(const connect_type& tc, const std::string& ip_, const int& port_)
        : type_connect_(tc)
        , ip_(ip_)
        , port_(port_) {}

    std::string connection_identifying::to_string() const {
        std::string qq;
        qq.append(std::to_string(type_connect_)).append("://").append(ip_).append(":").append(std::to_string(port_));
        return qq;
    }

    const std::string& connection_identifying::ip() const {
        return ip_;
    }

    const int& connection_identifying::port() const {
        return port_;
    }

    bool connection_identifying::operator==(const connection_identifying& ci) const {
        return (type_connect_ == ci.type_connect_ && ip_ == ci.ip_ && port_ == ci.port_);
    }
}
} // namespace actor_zeta::network

namespace std {
    std::string to_string(actor_zeta::network::connect_type tc) {
        std::string tmp;
        switch (tc) {
            case actor_zeta::network::connect_type::tcp: {
                tmp = "tcp";
                break;
            }

            case actor_zeta::network::connect_type::udp: {
                tmp = "udp";
                break;
            }
        }
        return tmp;
    }

    std::string to_string(actor_zeta::network::connection_identifying ci) {
        return ci.to_string();
    }

} // namespace std
