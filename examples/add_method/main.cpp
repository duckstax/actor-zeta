#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>
#include <iterator>

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
    storage_t(abstract_environment *ptr) : basic_async_actor(ptr, "storage") {
        attach(
                make_handler(
                        "update",
                        [](context& /*ctx*/) -> void {


                        }
                )
        );

        attach(
                make_handler(
                        "find",
                        []( context& /*ctx*/) -> void {

                        }
                )
        );

        attach(
                make_handler(
                        "remove",
                        []( context& /*ctx*/ ) -> void {

                        }
                )
        );
    }


    ~storage_t() override = default;


private:
    std::unordered_map<std::string, std::string> storage_;

};


int main() {

    auto *storage_tmp = new storage_t(nullptr);

    actor_zeta::actor::actor storage(storage_tmp);

    assert(std::string("storage") == storage->name());

    auto tmp = storage->message_types();

    std::set<std::string> control = {"add_channel", "skip", "sync_contacts", "update", "remove", "find"};

    std::set<std::string> diff;

    std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));

    assert(diff.empty());

    return 0;
}