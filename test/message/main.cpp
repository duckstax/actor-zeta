#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("message") {
    SECTION("simple") {
        message msg;
        REQUIRE(msg.operator bool() == false);
        message msg_1(address_t::empty_address(), "1", int(1));
        REQUIRE(msg_1.operator bool() == true);
        REQUIRE(msg_1.command() == "1");
        REQUIRE(msg_1.body<int>() == 1);
    }
}
