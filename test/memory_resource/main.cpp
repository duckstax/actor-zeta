#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("memory_resource") {
    SECTION("derived_from_memory_resource allocate") {
        derived_from_memory_resource d;
        memory_resource& mr = d;

        d.reset();
        REQUIRE(d.do_allocate_called == false);
        REQUIRE(d.do_allocate_bytes == 0);
        REQUIRE(d.do_allocate_alignment == 0);

        mr.allocate(2, 4);
        REQUIRE(d.do_allocate_called == true);
        REQUIRE(d.do_allocate_bytes == 2);
        REQUIRE(d.do_allocate_alignment == 4);
    }

    SECTION("derived_from_memory_resource deallocate") {
        derived_from_memory_resource d;
        memory_resource& mr = d;

        d.reset();
        REQUIRE(d.do_deallocate_called == false);
        REQUIRE(d.do_deallocate_p == 0);
        REQUIRE(d.do_allocate_bytes == 0);
        REQUIRE(d.do_allocate_alignment == 0);

        mr.deallocate(&d, 2, 4);
        REQUIRE(d.do_deallocate_called == true);
        REQUIRE(d.do_deallocate_p == &d);
        REQUIRE(d.do_deallocate_bytes == 2);
        REQUIRE(d.do_deallocate_alignment == 4);
    }

    SECTION("derived_from_memory_resource destructor_called") {
        {
            derived_from_memory_resource d;
            d.reset();
            REQUIRE(derived_from_memory_resource::destructor_called == false);
        }
        REQUIRE(derived_from_memory_resource::destructor_called == true);
    }

    SECTION("derived_from_memory_resource reset is_equal") {
        derived_from_memory_resource d;
        memory_resource& mr = d;

        d.reset();
        REQUIRE(d.do_is_equal_called == false);
        REQUIRE(d.do_is_equal_other == 0);

        mr.is_equal(d);
        REQUIRE(d.do_is_equal_called == true);
        REQUIRE(d.do_is_equal_other == &d);
    }

    SECTION("derived_from_memory_resource reset is_equal other") {
        derived_from_memory_resource d;
        memory_resource& mr = d;

        d.reset();
        REQUIRE(d.do_is_equal_called == false);
        REQUIRE(d.do_is_equal_other == 0);

        REQUIRE((mr == mr) == true);
        REQUIRE(d.do_is_equal_called == false);
        REQUIRE(d.do_is_equal_other == 0);

        derived_from_memory_resource d2(1);
        d.reset();
        d2.reset();
        memory_resource& mr2 = d2;
        REQUIRE((mr == mr2) == false);
        REQUIRE(d.do_is_equal_called == true);
        REQUIRE(d.do_is_equal_other == &d2);
    }

    SECTION("derived_from_memory_resource all") {
        derived_from_memory_resource d;
        memory_resource& mr = d;

        d.reset();
        REQUIRE(d.do_is_equal_called == false);
        REQUIRE(d.do_is_equal_other == 0);

        REQUIRE((mr != mr) == false);
        REQUIRE(d.do_is_equal_called == false);
        REQUIRE(d.do_is_equal_other == 0);

        derived_from_memory_resource d2(1);
        d.reset();
        d2.reset();
        memory_resource& mr2 = d2;
        REQUIRE((mr != mr2) == true);
        REQUIRE(d.do_is_equal_called == true);
        REQUIRE(d.do_is_equal_other == &d2);
    }
}
