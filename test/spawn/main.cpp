#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"
#include <cassert>

#include <set>
#include <string>

#include <actor-zeta.hpp>
#include <test/tooltestsuites/scheduler_test.hpp>

using actor_zeta::pmr::memory_resource;
class dummy_supervisor;

static std::atomic_int actor_counter{0};
static std::atomic_int supervisor_counter{0};
static std::atomic_int supervisor_sub_counter{0};

constexpr const static auto update_id = actor_zeta::make_message_id(0);
constexpr const static auto find_id = actor_zeta::make_message_id(1);
constexpr const static auto remove_id = actor_zeta::make_message_id(2);

constexpr const static auto create_actor_id = actor_zeta::make_message_id(0);
constexpr const static auto create_supervisor_id = actor_zeta::make_message_id(1);
constexpr const static auto create_supervisor_custom_resource_id = actor_zeta::make_message_id(2);

class dummy_supervisor;
class storage_t;

class dummy_supervisor_sub final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor_sub(dummy_supervisor* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr)
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        ///auto * ptr_sheduler = scheduler();
        ///ptr_sheduler->start();
        executor_->start();
        supervisor_sub_counter++;
    }

    dummy_supervisor_sub(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr)
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        ///scheduler()->start();
        executor_->start();
        supervisor_sub_counter++;
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    auto make_type() const noexcept -> const char* const {
        return "dummy_supervisor_sub";
    }

    auto make_scheduler() noexcept -> actor_zeta::scheduler_abstract_t* {
        return executor_.get();
    }

protected:
    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [](actor_zeta::message*) -> void {

            });
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            behavior()(current_message());
        }
    }

private:
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
};

class dummy_supervisor final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr)
        , create_actor_(actor_zeta::make_behavior(resource(), create_actor_id, this, &dummy_supervisor::create_actor))
        , create_supervisor_(actor_zeta::make_behavior(resource(), create_supervisor_id, this, &dummy_supervisor::create_supervisor))
        , create_supervisor_custom_resource_(actor_zeta::make_behavior(resource(), create_supervisor_custom_resource_id, this, &dummy_supervisor::create_supervisor_custom_resource))
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        scheduler()->start();
        supervisor_counter++;
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    void create_actor() {
        spawn_actor([this](storage_t* ptr) {
            actors_.emplace_back(ptr);
        });
    }

    void create_supervisor() {
        spawn_supervisor(
            [this](dummy_supervisor_sub* ptr) {
                supervisor_.emplace_back(ptr);
            },
            this);
    }

    void create_supervisor_custom_resource() {
        spawn_supervisor(
            [this](dummy_supervisor_sub* ptr) {
                supervisor_.emplace_back(ptr);
            },
            resource());
    }

    auto make_type() const noexcept -> const char* const {
        return "dummy_supervisor";
    }

    auto make_scheduler() noexcept -> actor_zeta::scheduler_abstract_t* {
        return executor_.get();
    }

protected:
    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case create_actor_id: {
                        create_actor_(msg);
                        break;
                    }
                    case create_supervisor_id: {
                        create_supervisor_(msg);
                        break;
                    }
                    case create_supervisor_custom_resource_id: {
                        create_supervisor_custom_resource_(msg);
                        break;
                    }
                }
            });
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            behavior()(current_message());
        }
    }

private:
    actor_zeta::behavior_t create_actor_;
    actor_zeta::behavior_t create_supervisor_;
    actor_zeta::behavior_t create_supervisor_custom_resource_;
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::vector<actor_zeta::actor_t> actors_;
    std::vector<actor_zeta::supervisor_t> supervisor_;
};

class storage_t final : public actor_zeta::basic_actor<storage_t> {
public:
    storage_t(dummy_supervisor* ptr)
        : actor_zeta::basic_actor<storage_t>(ptr)
        , update_(actor_zeta::make_behavior(resource(), update_id, []() -> void {}))
        , find_(actor_zeta::make_behavior(resource(), find_id, []() -> void {}))
        , remove_(actor_zeta::make_behavior(resource(), remove_id, []() -> void {})) {
        REQUIRE(std::string("storage") == type());
        actor_counter++;
    }

    auto make_type() const noexcept -> const char* const {
        return "storage";
    }

    ~storage_t() override = default;

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case update_id: {
                        update_(msg);
                        break;
                    }
                    case find_id: {
                        find_(msg);
                        break;
                    }
                    case remove_id: {
                        remove_(msg);
                        break;
                    }
                }
            });
    }

private:
    actor_zeta::behavior_t update_;
    actor_zeta::behavior_t find_;
    actor_zeta::behavior_t remove_;
};

TEST_CASE("spawn base supervisor") {
    supervisor_counter = 0;
    actor_counter = 0;
    auto* mr_ptr = actor_zeta::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    REQUIRE(supervisor_counter == 1);
}

TEST_CASE("spawn supervisor") {
    supervisor_counter = 0;
    supervisor_sub_counter = 0;
    actor_counter = 0;
    auto* mr_ptr = actor_zeta::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), create_supervisor_id);
    supervisor->scheduler_test()->run_once();
    REQUIRE(supervisor_counter == 1);
    REQUIRE(supervisor_sub_counter == 1);
}

TEST_CASE("spawn supervisor custom resource") {
    supervisor_counter = 0;
    supervisor_sub_counter = 0;
    actor_counter = 0;
    auto* mr_ptr = actor_zeta::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), create_supervisor_custom_resource_id);
    supervisor->scheduler_test()->run_once();
    REQUIRE(supervisor_counter == 1);
    REQUIRE(supervisor_sub_counter == 1);
}

TEST_CASE("spawn actor") {
    supervisor_counter = 0;
    actor_counter = 0;
    auto* mr_ptr = actor_zeta::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), create_actor_id);
    supervisor->scheduler_test()->run_once();
    REQUIRE(actor_counter == 1);
}
