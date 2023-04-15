#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <cassert>

#include <map>
#include <set>
#include <string>

#include <actor-zeta.hpp>
#include <test/tooltestsuites/scheduler_test.hpp>

using actor_zeta::pmr::memory_resource;
class dummy_supervisor;
class storage_t;

enum class command_t {
    create = 0x00
};

class dummy_supervisor final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr)
        , create_(resource())
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        actor_zeta::make_behavior(create_,command_t::create,this, &dummy_supervisor::create);
        scheduler()->start();
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    void create() ;

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
                    case actor_zeta::make_message_id(command_t::create): {
                        create_(msg);
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
    actor_zeta::behavior_t create_;
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::set<int64_t> ids_;
};


class storage_t final : public actor_zeta::basic_actor<storage_t> {
public:
    storage_t(dummy_supervisor* ptr)
        : actor_zeta::basic_actor<storage_t>(ptr) {
    }

    auto make_type() const noexcept -> const char* const {
        return "storage";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {

            });
    }

    ~storage_t() override = default;
};

void dummy_supervisor::create() {
    spawn_actor([this](storage_t* ptr) {
        REQUIRE(actor_zeta::base::actor_abstract::id_t(static_cast<actor_zeta::base::actor_abstract*>(ptr)) == ptr->id());
        REQUIRE(ids_.find(reinterpret_cast<int64_t>(ptr)) == ids_.end());
        ids_.insert(reinterpret_cast<int64_t>(ptr));
    });
}

TEST_CASE("actor id match") {
    auto* mr_ptr = actor_zeta::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    for (auto i = 0; i < 1000; ++i) { //todo: 10000000
        actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), command_t::create);
        supervisor->scheduler_test()->run_once();
    }
}
