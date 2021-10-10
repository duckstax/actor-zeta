#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("string_view") {
    SECTION("simple") {
        string_view x;
        string_view y;
        REQUIRE(x.empty());
        REQUIRE(x.size() == 0u);
        REQUIRE(x.data() == nullptr);
        REQUIRE(y == y);
    }

    SECTION("compare") {
        string_view x("abc");
        REQUIRE(x.size() == 3u);
        REQUIRE(x == string_view("abc"));
    }
}
