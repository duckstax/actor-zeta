#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("metaprogramming") {
    SECTION("simple") {
        REQUIRE((is_same<int, type_list_at<l1, 0>::type>::value));
        REQUIRE((is_same<float, type_list_at<l1, 1>::type>::value));
        REQUIRE((is_same<std::string, type_list_at<l1, 2>::type>::value));
        REQUIRE(3u == type_list_size<l1>::value);
        REQUIRE(type_list_size<r1>::value == type_list_size<l1>::value);
        REQUIRE((is_same<type_list_at<l1, 0>::type, type_list_at<r1, 2>::type>::value));
        REQUIRE((is_same<type_list_at<l1, 1>::type, type_list_at<r1, 1>::type>::value));
        REQUIRE((is_same<type_list_at<l1, 2>::type, type_list_at<r1, 0>::type>::value));
    }
}
