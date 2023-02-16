#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>


#include <actor-zeta.hpp>

static int free_function_arg_0_counter = 0 ;
static int free_function_arg_2_counter = 0 ;

void free_function_arg_0() {
    free_function_arg_0_counter = 1;
    REQUIRE(free_function_arg_0_counter == 1);
}

void free_function_arg_2(int arg_0, int arg_1){
    free_function_arg_2_counter = 1;
    REQUIRE(arg_0 == 21);
    REQUIRE(arg_1 == 42);
    REQUIRE(free_function_arg_2_counter == 1);
}

enum class size_args : uint64_t {
    args_0 = 0x00,
    args_1,
    args_2,
    args_3,
    args_4
};

TEST_CASE("behavior") {
    SECTION("free function arg 0") {
        actor_zeta::detail::pmr::memory_resource* resource = actor_zeta::detail::pmr::get_default_resource();
        actor_zeta::behavior_t free_function(resource);
        actor_zeta::behavior(free_function, size_args::args_0, free_function_arg_0);
        auto msg = actor_zeta::make_message(actor_zeta::address_t::empty_address(), size_args::args_0);
        free_function(msg.get());
    }

    SECTION("free function arg 2") {
        actor_zeta::detail::pmr::memory_resource* resource = actor_zeta::detail::pmr::get_default_resource();
        actor_zeta::behavior_t free_function(resource);
        actor_zeta::behavior(free_function, size_args::args_2, free_function_arg_2);
        auto msg = actor_zeta::make_message(actor_zeta::address_t::empty_address(), size_args::args_2, 21, 42);
        free_function(msg.get());
    }
}