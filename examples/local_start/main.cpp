#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>

#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/basic_actor.hpp>

using actor_zeta::behavior::make_handler;
using actor_zeta::behavior::context;
using actor_zeta::messaging::make_message;
using actor_zeta::environment::abstract_environment;
using actor_zeta::actor::basic_async_actor;


class storage_t final : public basic_async_actor {
public:
    storage_t(abstract_environment *ptr): basic_async_actor(ptr,"storage"){
        attach(
                make_handler(
                        "update",
                        [this]( context& ctx ) -> void {

                        std::cerr<<"update"<<std::endl;

                        }
                )
        );

        attach(
                make_handler(
                        "find",
                        [this]( context& ctx ) -> void {

                        std::cerr<<"find"<<std::endl;

                        }
                )
        );

        attach(
                make_handler(
                        "remove",
                        [this]( context& ctx ) -> void {

                        std::cerr<<"remove"<<std::endl;

                        }
                )
        );



    }

    ~storage_t() override = default;


private:

};



int main() {

    auto* storage_tmp = new storage_t(nullptr);

    actor_zeta::actor::actor storage(storage_tmp);

    storage->send(
        make_message(
                actor_zeta::actor::actor_address(),
                "update",
                std::string("payload")
        )
    );

    storage->send(
            make_message(
                    actor_zeta::actor::actor_address(),
                    "find",
                    std::string("payload")
            )
    );

    storage->send(
            make_message(
                    actor_zeta::actor::actor_address(),
                    "remove",
                    std::string("payload")
            )
    );

    storage_tmp->launch(nullptr, false);

    return 0;
}