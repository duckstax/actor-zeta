#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("spawn-actor actor") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr, mr_ptr);
    actor_zeta::send(supervisor->resource(), supervisor.get(), actor_zeta::address_t::empty_address(), create_id);
    supervisor->scheduler_test()->run_once();
    REQUIRE(actor_counter == 1);
}
