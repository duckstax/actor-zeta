#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("intrusive_ptr") {
    SECTION("make_counted") {
        auto p = make_counted<class0>();
        REQUIRE(class0_instances == 1);
        REQUIRE(p->unique() == true);
    }

    SECTION("reset") {
        class0ptr p0;
        p0.reset(new class0, false);
        REQUIRE(class0_instances == 1);
        REQUIRE(bool(p0->unique()) == true);
    }

    SECTION("get_test_rc") {
        class0ptr p1;
        p1 = get_test_rc();
        class0ptr p2 = p1;
        REQUIRE(class0_instances == 1);
        REQUIRE(p1->unique() == false);
    }

    SECTION("list") {
        std::vector<class0ptr> pl;
        pl.push_back(get_test_ptr());
        pl.push_back(get_test_rc());
        pl.push_back(pl.front()->create());
        REQUIRE(pl.front()->unique());
        REQUIRE(class0_instances == 3);
    }

    SECTION("full_test") {
        auto p1 = make_counted<class0>();
        REQUIRE(p1->is_subtype() == false);
        REQUIRE(p1->unique() == true);
        REQUIRE(class0_instances == 1);
        REQUIRE(class1_instances == 0);
        p1.reset(new class1, false);
        REQUIRE(p1->is_subtype() == true);
        REQUIRE(p1->unique() == true);
        REQUIRE(class0_instances == 0);
        REQUIRE(class1_instances == 1);
        auto p2 = make_counted<class1>();
        p1 = p2;
        REQUIRE(p1->unique() == false);
        REQUIRE(class0_instances == 0);
        REQUIRE(class1_instances == 1);
        REQUIRE(p1 == static_cast<class0*>(p2.get()));
    }
}
