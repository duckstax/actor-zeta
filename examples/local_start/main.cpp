#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::context;
using actor_zeta::send;

class storage_t final : public basic_async_actor {
public:
    storage_t() : basic_async_actor(nullptr, "storage") {
        add_handler(
                "update",
                [](context & /*ctx*/, std::string &data) -> void {
                    std::cerr << "update:" << data << std::endl;
                }
        );

        add_handler(
                "find",
                [](context & /*ctx*/) -> void {
                    std::cerr << "find" << std::endl;
                }
        );

        add_handler(
                "remove",
                [](context & /*ctx*/) -> void {
                    std::cerr << "remove" << std::endl;
                }
        );

    }

    ~storage_t() override = default;

};


int main() {

    auto* storage = new storage_t();
    send(storage,actor_zeta::actor::actor_address(),"update",std::string("payload"));
    send(storage,actor_zeta::actor::actor_address(),"find",std::string("payload"));
    send(storage,actor_zeta::actor::actor_address(),"remove",std::string("payload"));

    return 0;
}