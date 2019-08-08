#include <cassert>

#include <map>
#include <vector>

#include <actor-zeta/core.hpp>

using actor_zeta::context;
using actor_zeta::basic_async_actor;


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

    std::set<std::string> control = {"sync_contacts","add_link","remove_link", "update", "remove", "find"};

    std::set<std::string> diff;

    std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));

    assert(diff.empty());

    return 0;
}