#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("polymorphic_allocator") {
    REQUIRE(std::is_destructible<test_type>{});
    REQUIRE(std::is_copy_constructible<test_type>{});
    ///REQUIRE(std::is_copy_assignable<test_type>{}); ///TODO: hack
    REQUIRE(std::is_constructible<test_type, memory_resource*>{});
    REQUIRE(std::is_same<test_type::value_type, x>{});
    REQUIRE(!std::is_polymorphic<test_type>{});
#if CPP17_OR_GREATER or CPP14_OR_GREATER
    REQUIRE(!std::is_final<test_type>{});
#endif
    SECTION("resource_constructor") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> b(&d);
        REQUIRE(&d == b.resource());
    }

    SECTION("copy_constructor") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> b(&d);
        polymorphic_allocator<int> c(b);
        REQUIRE(b.resource() == c.resource());
    }

    SECTION("copy_assignment") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> b(&d);
        auto c = b;
        REQUIRE(c.resource() == b.resource());
    }

    SECTION("allocate") {
        int dummy;
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        d.reset();
        d.do_allocate_return = &dummy;
        p.allocate(2);
        REQUIRE(d.do_allocate_called == true);
        REQUIRE(d.do_allocate_return == &dummy);
        //It shall allocate 2*sizeof(int), alignment_of<int>
        REQUIRE(d.do_allocate_bytes == 2 * sizeof(int));
        REQUIRE(d.do_allocate_alignment == std::alignment_of<int>::value);
    }

    SECTION("deallocate") {
        int dummy;
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        d.reset();
        p.deallocate(&dummy, 3);
        REQUIRE(d.do_deallocate_called == true);
        //It shall deallocate 2*sizeof(int), alignment_of<int>
        REQUIRE(d.do_deallocate_p == &dummy);
        REQUIRE(d.do_deallocate_bytes == 3 * sizeof(int));
        REQUIRE(d.do_deallocate_alignment == std::alignment_of<int>::value);
    }

    SECTION("construct") {
        {
            using value_type = x;
            value_type value;
            value.~value_type();
            derived_from_memory_resource d;
            polymorphic_allocator<int> pa(&d);
            pa.construct(&value);
            REQUIRE(value.value_ == 0);
            value.~value_type();
        }

        {
            using value_type = x;
            value_type value;
            value.~value_type();
            derived_from_memory_resource d;
            polymorphic_allocator<int> pa(&d);
            pa.construct(&value, 2);
            REQUIRE(value.value_ == 2);
            value.~value_type();
        }
    }

    SECTION("destroy") {
        char_holder ch;
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        REQUIRE(char_holder::destructor_called == false);
        p.destroy(&ch);
        REQUIRE(char_holder::destructor_called == true);
    }

    SECTION("resource") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        REQUIRE(&d == p.resource());
    }
}
