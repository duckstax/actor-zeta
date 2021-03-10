#include <cassert>

#include <set>
#include <string>

#include <actor-zeta.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::supervisor_t;
using actor_zeta::message;
using actor_zeta::execution_device;

class dummy_supervisor final : public supervisor_t {
public:
    dummy_supervisor(): supervisor_t("dummy_supervisor"){}

    auto executor() noexcept -> actor_zeta::abstract_executor* override  {
        return ptr_;
    }

    auto join(actor_zeta::actor) -> actor_zeta::actor_address override {
        return actor_zeta::actor_address();
    }

    void enqueue_base(actor_zeta::message_ptr, execution_device *) override {}

private:
    actor_zeta::abstract_executor*ptr_ = nullptr;
};

class storage_t final : public basic_async_actor {
public:
    storage_t(dummy_supervisor*ptr) : basic_async_actor(ptr, "storage") {
        add_handler(
                "update",
                []() -> void {}
        );

        add_handler(
                "find",
                []() -> void {}
        );

        add_handler(
                "remove",
                []() -> void {}
        );
    }

    ~storage_t() override = default;
};


int main() {

    auto * supervisor = new dummy_supervisor;

    auto *storage_tmp = new storage_t(supervisor);

    actor_zeta::actor storage(storage_tmp);

    assert(actor_zeta::detail::string_view("storage") == storage->type());

    auto tmp = storage->message_types();

    std::set<std::string> control = {"add_link","remove_link", "update", "remove", "find"};

    std::set<std::string> diff;

    std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));

    assert(diff.empty());

    return 0;
}