#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("timer") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<supervisor_lite>(mr_ptr);

    auto& clock = supervisor->clock();
    auto time = clock.now() + std::chrono::seconds(10);
    clock.schedule_message(time, supervisor->address(), actor_zeta::make_message(actor_zeta::address_t::empty_address(), alarm_id));
    supervisor->clock().advance_time(std::chrono::seconds(10));

    REQUIRE(alarm_counter.load() == 1);
}
