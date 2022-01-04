#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

#include <cassert>

#include <set>
#include <string>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <test/tooltestsuites/scheduler_test.hpp>

#include <actor-zeta/base/actor_schedule.hpp>

using actor_zeta::detail::pmr::memory_resource;
class dummy_supervisor;

static std::atomic_int actor_counter{0};

class storage_t final : public actor_zeta::base::actor_schedule<storage_t> {
public:
    storage_t(dummy_supervisor* ptr)
        : actor_zeta::base::actor_schedule<storage_t>(ptr, "storage", 0) {

        behavior([this](actor_zeta::base::behavior_t&behavior){
            add_handler(behavior,"update", []() -> void {});
            add_handler(behavior,"find", []() -> void {});
            add_handler(behavior,"remove", []() -> void {});
        });

        actor_counter++;
    }

    ~storage_t() override = default;
};

class dummy_supervisor final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr, "dummy_supervisor", 0)
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        behavior([this](actor_zeta::base::behavior_t& behavior) {
            add_handler(behavior, "create", &dummy_supervisor::create);
        });
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
            ///execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::vector<actor_zeta::actor> actors_;
};

TEST_CASE("behavior simple") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), "create");
    supervisor->scheduler_test()->run_once();
    REQUIRE(actor_counter == 1);
}