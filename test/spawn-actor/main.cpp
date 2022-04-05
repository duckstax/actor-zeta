#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"
#include <cassert>

#include <set>
#include <string>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <test/tooltestsuites/scheduler_test.hpp>

using actor_zeta::detail::pmr::memory_resource;
class dummy_supervisor;

static std::atomic_int actor_counter{0};

constexpr const static auto update_id = actor_zeta::make_message_id(0);
constexpr const static auto find_id  = actor_zeta::make_message_id(1);
constexpr const static auto remove_id  = actor_zeta::make_message_id(2);

class storage_t final : public actor_zeta::basic_async_actor {
public:
    storage_t(dummy_supervisor* ptr)
        : actor_zeta::basic_async_actor(ptr, "storage") {
        add_handler(update_id, []() -> void {});
        add_handler(find_id, []() -> void {});
        add_handler(remove_id, []() -> void {});

        REQUIRE(actor_zeta::detail::string_view("storage") == type());
        auto tmp = message_types();
        std::set<actor_zeta::message_id> control = {update_id, remove_id, find_id};
        std::set<actor_zeta::message_id> diff;
        std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));
        REQUIRE(diff.empty());
        actor_counter++;
    }

    ~storage_t() override = default;
};

constexpr const static auto create_id = actor_zeta::make_message_id(0);

class dummy_supervisor final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr, "dummy_supervisor")
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        add_handler(create_id, &dummy_supervisor::create);
        scheduler()->start();
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    void create() {
        spawn_actor<storage_t>([this](storage_t* ptr) {
            actors_.emplace_back(ptr);
        });
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* override {
        return executor_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            execute(this,current_message());
        }
    }

private:
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::vector<actor_zeta::actor> actors_;
};

TEST_CASE("spawn-actor actor") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), create_id);
    supervisor->scheduler_test()->run_once();
    REQUIRE(actor_counter == 1);
}
