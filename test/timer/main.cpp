#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <cassert>

#include <chrono>
#include <memory>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

#include "classes.hpp"
#include "tooltestsuites/scheduler_test.hpp"

static std::atomic<uint64_t> alarm_counter{0};

using actor_zeta::detail::pmr::memory_resource;
/// non thread safe
class supervisor_lite final : public actor_zeta::cooperative_supervisor<supervisor_lite> {
public:
    explicit supervisor_lite(memory_resource* ptr)
        : cooperative_supervisor(ptr, "network")
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        add_handler("alarm", &supervisor_lite::alarm);
        scheduler()->start();
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    ~supervisor_lite() override = default;

    void alarm() {
        alarm_counter += 1;
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final { return executor_.get(); }
    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::vector<actor_zeta::actor> actors_;
};

TEST_CASE("timer") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<supervisor_lite>(mr_ptr);

    auto time = supervisor->clock().now() + std::chrono::seconds(10);
    supervisor->clock().schedule_message(time, supervisor->address(), actor_zeta::make_message(actor_zeta::address_t::empty_address(), "alarm"));
    supervisor->scheduler_test()->advance_time(std::chrono::seconds(10));

    REQUIRE(alarm_counter.load() == 1);
}
