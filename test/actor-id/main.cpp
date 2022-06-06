#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <cassert>

#include <map>
#include <set>
#include <string>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <test/tooltestsuites/scheduler_test.hpp>

using actor_zeta::detail::pmr::memory_resource;
class dummy_supervisor;

class storage_t final : public actor_zeta::basic_async_actor {
public:
    storage_t(dummy_supervisor* ptr)
        : actor_zeta::basic_async_actor(ptr, "storage") {
    }

    ~storage_t() override = default;
};

enum class command_t {
    create = 0x00
};

class dummy_supervisor final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr, "dummy_supervisor")
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        add_handler(command_t::create, &dummy_supervisor::create);
        scheduler()->start();
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    void create() {
        spawn_actor([this](storage_t* ptr) {
            REQUIRE(actor_zeta::base::actor_abstract::id_t(static_cast<actor_zeta::base::actor_abstract*>(ptr)) == ptr->id());
            REQUIRE(ids_.find(reinterpret_cast<int64_t>(ptr)) == ids_.end());
            ids_.insert(reinterpret_cast<int64_t>(ptr));
        });
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* override {
        return executor_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            execute(this, current_message());
        }
    }

private:
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::set<int64_t> ids_;
};

TEST_CASE("actor id match") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    for (auto i = 0; i < 1000; ++i) { //todo: 10000000
        actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), command_t::create);
        supervisor->scheduler_test()->run_once();
    }
}
