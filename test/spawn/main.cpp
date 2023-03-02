#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"
#include <cassert>

#include <set>
#include <string>

#include <actor-zeta.hpp>
#include <test/tooltestsuites/scheduler_test.hpp>

using actor_zeta::detail::pmr::memory_resource;
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
    dummy_supervisor_sub(dummy_supervisor* ptr, std::string name)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr)
        , name_(std::move(name))
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        scheduler()->start();
        supervisor_sub_counter++;
    }

    dummy_supervisor_sub(memory_resource* ptr, std::string name)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr)
        , name_(std::move(name))
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        scheduler()->start();
        supervisor_sub_counter++;
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    auto make_type() /*const*/ noexcept -> const char* const {
        return name_.c_str();
    }

protected:
    actor_zeta::behavior_t make_behavior() {
        return actor_zeta::behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {

            });
    }

    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* override {
        return executor_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            make_behavior()(current_message());
        }
    }

private:
    std::string  name_;
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
};

class dummy_supervisor final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr)
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        add_handler(create_actor_id, &dummy_supervisor::create_actor);
        add_handler(create_supervisor_id, &dummy_supervisor::create_supervisor);
        add_handler(create_supervisor_custom_resource_id, &dummy_supervisor::create_supervisor_custom_resource);
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
            this, std::string("test_name"));
    }

    void create_supervisor_custom_resource() {
        spawn_supervisor(
            [this](dummy_supervisor_sub* ptr) {
                supervisor_.emplace_back(ptr);
            },
            actor_zeta::detail::pmr::get_default_resource(), std::string("test_name"));
    }

    auto make_type() /*const*/ noexcept -> const char* const {
        return "dummy_supervisor";
    }

protected:
    actor_zeta::behavior_t make_behavior() {
        return actor_zeta::behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {

            });
    }

    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* override {
        return executor_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            make_behavior()(current_message());
        }
    }

private:
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::vector<actor_zeta::actor_t> actors_;
    std::vector<actor_zeta::supervisor_t> supervisor_;
};



class storage_t final : public actor_zeta::basic_actor<storage_t> {
public:
    storage_t(dummy_supervisor* ptr)
        : actor_zeta::basic_actor<storage_t>(ptr)
        , update_(resource())
        , find_(resource())
        , remove_(resource()) {

        actor_zeta::behavior(update_,update_id, []() -> void {});
        actor_zeta::behavior(find_,find_id, []() -> void {});
        actor_zeta::behavior(remove_,remove_id, []() -> void {});

        REQUIRE(std::string("storage") == type());
        actor_counter++;
    }

    auto make_type() /*const*/ noexcept -> const char* const {
        return "storage";
    }

    ~storage_t() override = default;
protected:
    actor_zeta::behavior_t make_behavior() {
        return actor_zeta::behavior(
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
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    REQUIRE(supervisor_counter == 1);
}

TEST_CASE("spawn supervisor") {
    supervisor_counter = 0;
    supervisor_sub_counter = 0;
    actor_counter = 0;
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
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
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), create_supervisor_custom_resource_id);
    supervisor->scheduler_test()->run_once();
    REQUIRE(supervisor_counter == 1);
    REQUIRE(supervisor_sub_counter == 1);
}

TEST_CASE("spawn actor") {
    supervisor_counter = 0;
    actor_counter = 0;
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), create_actor_id);
    supervisor->scheduler_test()->run_once();
    REQUIRE(actor_counter == 1);
}
