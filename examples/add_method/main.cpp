#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>
#include <iterator>

#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/basic_actor.hpp>

using actor_zeta::actor::context;
using actor_zeta::messaging::make_message;
using actor_zeta::actor::basic_async_actor;


class storage_t final : public basic_async_actor {
public:
    storage_t() : basic_async_actor(nullptr, "storage") {
        add_handler(
                "update",
                [](context & /*ctx*/) -> void {}
        );

        add_handler(
                "find",
                [](context & /*ctx*/) -> void {}
        );

        add_handler(
                "remove",
                [](context & /*ctx*/ ) -> void {}
        );
    }

    ~storage_t() override = default;
};


int main() {

    auto *storage_tmp = new storage_t;

    actor_zeta::actor::actor storage(storage_tmp);

    assert(actor_zeta::detail::string_view("storage") == storage->name());

    auto tmp = storage->message_types();

    std::set<std::string> control = {"skip", "sync_contacts", "update", "remove", "find"};

    std::set<std::string> diff;

    std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));

    assert(diff.empty());

    return 0;
}