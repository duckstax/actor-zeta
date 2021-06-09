#include <cassert>

#include <set>
#include <string>

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::supervisor;
using actor_zeta::message;
using actor_zeta::execution_device;

class dummy_supervisor final : public supervisor {
public:
    dummy_supervisor(): supervisor("dummy_supervisor"){}

    auto executor() noexcept -> actor_zeta::abstract_executor& override  {
        return *ptr_;
    }

    auto join(actor_zeta::actor) -> actor_zeta::actor_address override {
        return actor_zeta::actor_address();
    }

    void enqueue(message, execution_device *) override {}

private:
    actor_zeta::abstract_executor*ptr_ = nullptr;
};

class storage_t final : public basic_async_actor {
public:
    storage_t(dummy_supervisor&ref) : basic_async_actor(ref, "storage") {
        add_handler(
                "update",
                [](communication_module & /*ctx*/) -> void {}
        );

        add_handler(
                "find",
                [](communication_module & /*ctx*/) -> void {}
        );

        add_handler(
                "remove",
                [](communication_module & /*ctx*/ ) -> void {}
        );
    }

    ~storage_t() override = default;
};


int main() {

    auto * supervisor = new dummy_supervisor;

    auto *storage_tmp = new storage_t(*supervisor);

    actor_zeta::actor storage(storage_tmp);

    assert(actor_zeta::detail::string_view("storage") == storage->name());

    auto tmp = storage->message_types();

    std::set<std::string> control = {"add_link","remove_link", "update", "remove", "find"};

    std::set<std::string> diff;

    std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));

    assert(diff.empty());

    return 0;
}