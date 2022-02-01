#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <actor-zeta/detail/rtt.hpp>

#include "classes.hpp"

using actor_zeta::detail::rtt;

#ifdef __TESTS_ENABLED__
namespace rtt_test = actor_zeta::detail::rtt_test;
#endif

TEST_CASE("rt_tuple") {
    SECTION("with_pmr") {
        actor_zeta::detail::pmr::rtt r(static_cast<int8_t>(3457),
                                       static_cast<int64_t>(57),
                                       static_cast<int32_t>(45),
                                       static_cast<long>(63),
                                       static_cast<long long>(6348),
                                       static_cast<long double>(6754.9),
                                       static_cast<int16_t>(4563),
                                       static_cast<float>(5653),
                                       static_cast<double>(675.49),
                                       static_cast<unsigned long>(45645),
                                       static_cast<unsigned long long>(5573),
                                       static_cast<char>(57));
    }
    SECTION("test_getSize") {
        test_getSize(
            static_cast<int8_t>(3457),
            static_cast<int64_t>(57),
            static_cast<int32_t>(45),
            static_cast<long>(63),
            static_cast<long long>(6348),
            static_cast<long double>(6754.9),
            static_cast<int16_t>(4563),
            static_cast<float>(5653),
            static_cast<double>(675.49),
            static_cast<unsigned long>(45645),
            static_cast<unsigned long long>(5573),
            static_cast<char>(57));

        std::map<std::string, std::string> map_strstr;
        for (int i = 0; i < 1024; ++i) {
            for (int j = 0; j < 4096; ++j)
                map_strstr["base64_" + std::to_string(i)].push_back(static_cast<char>(j % 8));
        }

        test_getSize(
            map_strstr,
            static_cast<long long>(6348),
            static_cast<long double>(6754.9),
            static_cast<int16_t>(4563),
            map_strstr,
            static_cast<float>(5653),
            static_cast<double>(675.49),
            map_strstr);

        test_getSize(
            map_strstr,
            static_cast<long long>(6348),
            static_cast<long double>(6754.9),
            std::string("sekrjghkjsh8"),
            std::string("slkdjfghlkajshglkjsdfhglkjshglkjhsdflkgjhsdflkgh"),
            static_cast<int16_t>(4563),
            map_strstr,
            std::string("slkdjfghlkajshglkjsddf,ghkjy5o876394673984769834569843589734563465fhglkjshglkjhsdflkgjhsdflkgh"),
            static_cast<float>(5653),
            std::string("slkdjfghlkajshglkjsdsfgs3465345634563465fhglkjshglkjhsdflkgjhsdflkgh"),
            static_cast<double>(675.49),
            std::string("35673673467345756756856875679659567956"),
            map_strstr,
            std::string("slkdjfghlkajshglkjsdfhglkjshglkjhsdflkgjhsdflkgsdfihgshdfgosfogskjfgkshfghsdkfjhgh"));

        test_getSize(
            align_example_t{},
            align_example_t{{1, 2, 3}, 15, 12, {6, 7, 8}},
            align_example_t{{1, 2, 3}, 15, 12, {6, 7, 8}},
            align_example_t{{1, 2, 3}, 15, 12, {6, 7, 8}},
            align_example_t{{1, 2, 3}, 15, 12, {6, 7, 8}},
            align_example_t{{1, 2, 3}, 15, 12, {6, 7, 8}});
    }

    SECTION("test_getSize many strings") {
        std::vector<int> idxs;
        for (int i = 0; i < 1024; ++i) {
            idxs.push_back(i);
        }

        auto idx = GENERATE_REF(from_range(idxs));
        std::string test_str;
        for (int i = 0; i < idx; ++i)
            test_str.push_back(static_cast<char>(i % 8));

        test_getSize(
            test_str);

        test_getSize(
            test_str,
            test_str,
            test_str);

        test_getSize(
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str);

        test_getSize(
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str,
            test_str);
    }

    SECTION("test_getSize many maps of string string") {
        std::vector<int> idxs;
        for (int i = 0; i < 1024; ++i) {
            idxs.push_back(i);
        }

        auto idx = GENERATE_REF(from_range(idxs));
        std::map<std::string, std::string> test_map;
        for (int i = 0; i < idx; ++i)
            test_map[std::to_string(i)] = "kfjhgkjsgkhsha";

        test_getSize(
            test_map);

        test_getSize(
            test_map,
            test_map,
            test_map);

        test_getSize(
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map);

        test_getSize(
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map,
            test_map);
    }

#ifdef __TESTS_ENABLED__

    SECTION("ctors") {
        rtt_test::clear();
        {
            auto templated_rtt_ = rtt(87645);
            REQUIRE(rtt_test::templated_ctor_ == 1);
            REQUIRE(rtt_test::copy_ctor_ == 0);
            REQUIRE(rtt_test::const_copy_ctor_ == 0);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 1);
        rtt_test::clear();

        {
            auto templated_rtt_ = rtt(87645, 1, 3, 356356, "aljehrgiauhg", std::vector<int>{1, 2, 3, 4, 5});
            REQUIRE(rtt_test::templated_ctor_ == 1);
            REQUIRE(rtt_test::copy_ctor_ == 0);
            REQUIRE(rtt_test::const_copy_ctor_ == 0);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 1);
        rtt_test::clear();

        {
            auto default_rtt_ = rtt(); // defaulted (+1)
            REQUIRE(rtt_test::templated_ctor_ == 0);
            REQUIRE(rtt_test::copy_ctor_ == 0);
            REQUIRE(rtt_test::const_copy_ctor_ == 0);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 1);
        rtt_test::clear();

        {
            auto default_rtt_ = rtt();            // defaulted (+1)
            auto copied_rtt_ = rtt(default_rtt_); // non-const lvalue
            REQUIRE(rtt_test::templated_ctor_ == 0);
            REQUIRE(rtt_test::copy_ctor_ == 1);
            REQUIRE(rtt_test::const_copy_ctor_ == 0);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 2);
        rtt_test::clear();

        {
            const auto default_rtt_ = rtt();            // defaulted (+1)
            auto const_copied_rtt_ = rtt(default_rtt_); // const lvalue
            REQUIRE(rtt_test::templated_ctor_ == 0);
            REQUIRE(rtt_test::copy_ctor_ == 0);
            REQUIRE(rtt_test::const_copy_ctor_ == 1);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 2);
        rtt_test::clear();

        {
            auto default_rtt_ = rtt();                      // defaulted (+1)
            auto moved_rtt_ = rtt(std::move(default_rtt_)); // move rvalue
            REQUIRE(rtt_test::templated_ctor_ == 0);
            REQUIRE(rtt_test::copy_ctor_ == 0);
            REQUIRE(rtt_test::const_copy_ctor_ == 0);
            REQUIRE(rtt_test::move_ctor_ == 1);
        }
        REQUIRE(rtt_test::dtor_ == 2);
        rtt_test::clear();

        /* many ctors */

        {
            auto default_rtt_ = rtt(); // defaulted (+1)
            auto templated_1_rtt_ = rtt(std::vector<int>{1, 2, 3, 4, 5}, 767, 5);
            auto templated_2_rtt_ = rtt(87645, 1, 3, 356356, "aljehrgiauhg", std::vector<int>{1, 2, 3, 4, 5}, 457, 4567);

            REQUIRE(rtt_test::templated_ctor_ == 2);
            REQUIRE(rtt_test::copy_ctor_ == 0);
            REQUIRE(rtt_test::const_copy_ctor_ == 0);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 3);
        rtt_test::clear();

        {
            auto default_rtt_ = rtt(); // defaulted (+1)
            auto templated_1_rtt_ = rtt(std::vector<int>{1, 2, 3, 4, 5}, 767, 5);
            auto templated_2_rtt_ = rtt(87645, 1, 3, 356356, "aljehrgiauhg", std::vector<int>{1, 2, 3, 4, 5}, 457, 4567);
            auto moved_1_rtt_ = rtt(std::move(templated_1_rtt_)); // move rvalue
            auto moved_2_rtt_ = rtt(std::move(templated_2_rtt_)); // move rvalue
            auto moved_3_rtt_ = rtt(std::move(default_rtt_));     // move rvalue

            REQUIRE(rtt_test::templated_ctor_ == 2);
            REQUIRE(rtt_test::copy_ctor_ == 0);
            REQUIRE(rtt_test::const_copy_ctor_ == 0);
            REQUIRE(rtt_test::move_ctor_ == 3);
        }
        REQUIRE(rtt_test::dtor_ == 6);
        rtt_test::clear();

        {
            auto default_rtt_ = rtt();                        // defaulted (+1)
            const auto const_default_rtt_ = rtt();            // const defaulted (+1)
            auto copied_rtt_ = rtt(default_rtt_);             // non-const lvalue
            auto const_copied_rtt_ = rtt(const_default_rtt_); // const lvalue
            auto templated_1_rtt_ = rtt(std::vector<int>{1, 2, 3, 4, 5}, 767, 5);
            auto templated_2_rtt_ = rtt(87645, 1, 3, 356356, "aljehrgiauhg", std::vector<int>{1, 2, 3, 4, 5}, 457, 4567);

            REQUIRE(rtt_test::templated_ctor_ == 2);
            REQUIRE(rtt_test::copy_ctor_ == 1);
            REQUIRE(rtt_test::const_copy_ctor_ == 1);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 6);
        rtt_test::clear();

        {
            auto default_rtt_ = rtt();                                             // defaulted (+1)
            auto copied_rtt_ = rtt(default_rtt_);                                  // non-const lvalue
            auto const_copied_rtt_ = rtt(static_cast<const rtt<>&>(default_rtt_)); // const lvalue
            auto templated_1_rtt_ = rtt(std::vector<int>{1, 2, 3, 4, 5}, 767, 5);
            auto templated_2_rtt_ = rtt(87645, 1, 3, 356356, "aljehrgiauhg", std::vector<int>{1, 2, 3, 4, 5}, 457, 4567);

            REQUIRE(rtt_test::templated_ctor_ == 2);
            REQUIRE(rtt_test::copy_ctor_ == 1);
            REQUIRE(rtt_test::const_copy_ctor_ == 1);
            REQUIRE(rtt_test::move_ctor_ == 0);
        }
        REQUIRE(rtt_test::dtor_ == 5);
        rtt_test::clear();

        {
            auto templated_1_rtt_ = rtt(std::vector<int>{1, 2, 3, 4, 5});
            auto templated_2_rtt_ = rtt(87645, 1, 3, 356356, "aljehrgiauhg", std::vector<int>{1, 2, 3, 4, 5});
            auto default_rtt_ = rtt();                                             // defaulted (+1)
            auto copied_rtt_ = rtt(default_rtt_);                                  // non-const lvalue
            auto const_copied_rtt_ = rtt(static_cast<const rtt<>&>(default_rtt_)); // const lvalue
            auto moved_1_rtt_ = rtt(std::move(default_rtt_));                      // move rvalue
            auto moved_2_rtt_ = rtt(std::move(templated_1_rtt_));                  // move rvalue

            REQUIRE(rtt_test::templated_ctor_ == 2);
            REQUIRE(rtt_test::copy_ctor_ == 1);
            REQUIRE(rtt_test::const_copy_ctor_ == 1);
            REQUIRE(rtt_test::move_ctor_ == 2);
        }
        REQUIRE(rtt_test::dtor_ == 7);
        rtt_test::clear();
    }

#endif

    SECTION("rtt created from an empty set of elements is empty") {
        const auto t = rtt{};
        REQUIRE(t.empty());
    }

    SECTION("The size of a rtt created from an empty set of elements is zero ") {
        const auto t = rtt{};
        REQUIRE(t.size() == 0);
    }

    SECTION("The volume of a rtt created from an empty set of elements is zero ") {
        const auto t = rtt{};
        REQUIRE(t.volume() == 0);
    }

    SECTION("The capacity of a rtt created from an empty set of elements is zero ") {
        const auto t = rtt{};
        REQUIRE(t.capacity() == 0);
    }

    SECTION("rtt created from a non-empty set of elements is not empty ") {
        const auto t = rtt(42, 3.14);
        REQUIRE(not t.empty());
    }

    SECTION("The size of a rtt created from a non-empty set of elements is equal to the number of these elements ") {
        const auto t = rtt(std::string("123"), 42, 2.71, false);
        REQUIRE(t.size() == 4);
    }

    SECTION("The volume of a rtt created from a set of elements is equal to the volume of a rtt created by sequential insertion of the same elements into the end of an empty rtt. ") {
        const auto constructed = rtt(42, 3.14, std::string("123"), true);

        auto pushed_back = rtt{42, 3.14, std::string("123"), true};

        REQUIRE(constructed.volume() == pushed_back.volume());
    }

    SECTION("The capacity of a recreation center created from a set of elements is greater than or equal to the volume of this recreation center ") {
        const auto t = rtt(std::vector<std::size_t>{}, 42, X{}, 3.14);
        REQUIRE(t.capacity() >= t.volume());
    }

    SECTION("The size of the rtt is equal to the number of elements it contains") {
        const auto some_vector = std::vector<std::size_t>{};
        const auto some_integer = 42;
        const auto some_struct = X{};
        const auto some_floating = 3.14;

        rtt t(some_vector, some_integer, some_struct, some_floating);
        REQUIRE(t.size() == 4);
    }

    SECTION("rtt can be created from an arbitrary set of objects ") {
        rtt t(std::string("123"), 42, true, X{17, std::vector<int>{1, 2, 3}});
        REQUIRE(t.size() == 4);
        REQUIRE(t.get<std::string>(0) == std::string("123"));
        REQUIRE(t.get<int>(1) == 42);
        REQUIRE(t.get<bool>(2) == true);
        REQUIRE(t.get<X>(3).a == 17);
        REQUIRE(t.get<X>(3).b == std::vector<int>{1, 2, 3});
    }

    SECTION("Arbitrary objects can be inserted at the end of the rtt") {
        rtt t(X{17, std::vector<int>{1, 2, 3}}, true, std::string("123"));

        CHECK(t.size() == 3);
        CHECK(t.get<X>(0).a == 17);
        CHECK(t.get<X>(0).b == std::vector<int>{1, 2, 3});
        CHECK(t.get<bool>(1) == true);
        CHECK(t.get<std::string>(2) == std::string("123"));
    }

#ifndef __EXCEPTIONS_DISABLE__

    SECTION("The exception thrown by the inserted object does not result in leaks ") {
        REQUIRE(kamikaze::instances_count == 0);
        REQUIRE_THROWS_AS(rtt(kamikaze{}, kamikaze{}, kamikaze{}), std::runtime_error);
        CHECK(kamikaze::instances_count == 0);
    }

    /*SECTION("Exception when moving internal objects does not result in leaks") {
        const throw_on_move thrower{};

        REQUIRE(dummy::instances_count == 0);
        {
            rtt t;
            t.push_back(dummy{}); // non implemented method
            t.push_back(thrower); // non implemented method
            REQUIRE(dummy::instances_count == 1);

            REQUIRE_THROWS_AS(t.reserve(t.capacity() + 1), std::runtime_error);
            CHECK(dummy::instances_count == 1);
        }
        CHECK(dummy::instances_count == 0);
    }*/
    /*
duckstax/actor-zeta/test/rtt/main.cpp:262:36:   required from here
duckstax/actor-zeta/header/actor-zeta/detail/rtt_management.hpp:55:24: error: no matching function for call to ‘copy<std::unique_ptr<int, std::default_delete<int> > >(const void*&, void*&)’
   55 |                 copy<T>(source, destination);
duckstax/actor-zeta/header/actor-zeta/detail/rtt_management.hpp:20:10: note: candidate: ‘template<class T> std::enable_if_t<std::is_copy_constructible<_Tp>::value> actor_zeta::detail::management::copy(const void*, void*)’
   20 |     auto copy(const void* source, void* destination)
    SECTION("Throws an exception when trying to copy a non-copyable object") {
        std::unique_ptr<int> uptr(new int(5));
        rtt initial(std::move(uptr));
        rtt copied;
        CHECK_THROWS_AS(copied = initial, std::runtime_error);
    }

    SECTION("Exception when copying objects stored in the rtt does not lead to leaks") {
        REQUIRE(dummy::instances_count == 0);
        {
            std::unique_ptr<int> uptr(new int(17));
            rtt t(dummy{}, std::move(uptr), dummy{});
            REQUIRE(dummy::instances_count == 2);
            rtt copied;
            REQUIRE_THROWS_AS(copied = t, std::runtime_error);
            CHECK(dummy::instances_count == 2);
        }
        CHECK(dummy::instances_count == 0);
    }

    SECTION("Exception during copy assignment of objects stored in the rtt does not lead to leaks") {
        REQUIRE(dummy::instances_count == 0);
        {
            std::unique_ptr<int> uptr(new int(17));
            rtt t(dummy{}, std::move(uptr));
            rtt copy(dummy{});
            REQUIRE(dummy::instances_count == 2);

            REQUIRE_THROWS_AS(copy = t, std::runtime_error);
        }
        CHECK(dummy::instances_count == 0);
    }*/

#endif

    SECTION("Objects stored in the rtt can be changed externally ") {
        rtt t(true, std::vector<char>{'a', 'b', 'c'}, 10);

        auto& vector = t.get<std::vector<char>>(1);

        vector.push_back('q');
        CHECK(t.get<std::vector<char>>(1) == std::vector<char>{'a', 'b', 'c', 'q'});

        vector.clear();
        CHECK(t.get<std::vector<char>>(1).empty());
    }

    SECTION("The rtt transfer constructor transfers elements of one rtt into another, rather than inserting one rtt inside another rtt") {
        rtt moved(2.71, 3, false);
        rtt constructed(std::move(moved));
        CHECK(constructed.size() == 3);
    }

    SECTION("The rtt copy constructor copies the elements of one rtt to another, rather than inserting one rtt inside another rtt") {
        rtt copied(2.71, 3, false);
        rtt constructed(copied);
        CHECK(constructed.size() == 3);
    }

    SECTION("rtt may contain rtt") {
        rtt t(rtt(1, 2), rtt(3, 4));
        CHECK(t.size() == 2);
    }

    SECTION("Objects stored in the rtt are transferred when transferring the rtt") {
        REQUIRE(dummy::instances_count == 0);
        rtt one(dummy{});
        REQUIRE(dummy::instances_count == 1);

        rtt another(std::move(one));
        CHECK(dummy::instances_count == 1);

        one = std::move(another);
        CHECK(dummy::instances_count == 1);
    }

    SECTION("The rtt copy constructor creates new instances of objects stored in the copied rtt and destroys them when the created rtt copy is destroyed") {
        REQUIRE(dummy::instances_count == 0);
        {
            rtt initial(dummy{});

            REQUIRE(dummy::instances_count == 1);
            {
                rtt copy(initial);
                CHECK(dummy::instances_count == 2);
            }
            CHECK(dummy::instances_count == 1);
        }
        CHECK(dummy::instances_count == 0);
    }

    SECTION("The operator of the copying assignment of the rtt creates new instances of objects stored in the copied rtt and destroys them when this copy of the rtt is destroyed. ") {
        REQUIRE(dummy::instances_count == 0);
        {
            rtt initial(dummy{});

            REQUIRE(dummy::instances_count == 1);
            {
                rtt copy(dummy{});
                copy = initial;
                CHECK(dummy::instances_count == 2);
            }
            CHECK(dummy::instances_count == 1);
        }
        CHECK(dummy::instances_count == 0);
    }

    SECTION("Objects stored in the rtt are destroyed by copy assignment") {
        REQUIRE(dummy::instances_count == 0);
        rtt initial(dummy{});
        REQUIRE(dummy::instances_count == 1);

        rtt other(1, 3.14, true);
        initial = other;
        CHECK(dummy::instances_count == 0);
    }

    SECTION("Objects stored in the rtt are destroyed during transfer assignment") {
        REQUIRE(dummy::instances_count == 0);
        rtt initial(dummy{});
        REQUIRE(dummy::instances_count == 1);

        rtt other(1, 3.14, true);
        initial = std::move(other);
        CHECK(dummy::instances_count == 0);
    }

    SECTION("The transfer constructor leaves the portable rtt instance empty") {
        rtt source(13, 3.14, true);
        rtt destination(std::move(source));
        CHECK(source.empty());
    }

    SECTION("The takeover assignment operator leaves the portable copy of the rtt empty") {
        rtt source(std::string("move me"));
        rtt destination(std::string("some items here"));
        destination = std::move(source);
        CHECK(source.empty());
    }

    SECTION("The size of the rtt source after transfer is equal to zero") {
        rtt source(13, 3.14, true);
        rtt destination(std::move(source));
        CHECK(source.size() == 0);
    }

    SECTION("The size of the rtt-source after carrying assignment is equal to zero ") {
        rtt source(std::string("move me"));
        rtt destination(std::string("some items here"));
        destination = std::move(source);
        CHECK(source.size() == 0);
    }

    SECTION("The volume of the rtt source after transfer is equal to zero") {
        rtt source(13, 3.14, true);
        rtt destination(std::move(source));
        CHECK(source.volume() == 0);
    }

    SECTION("The volume of the rtt-source after carrying assignment is equal to zero") {
        rtt source(std::string("move me"));
        rtt destination(std::string("some items here"));
        destination = std::move(source);
        CHECK(source.volume() == 0);
    }

    SECTION("Copying a rtt leads to the creation of real copies of the objects stored in it") {
        rtt initial(std::string("cat"));

        auto copy = rtt(initial);
        REQUIRE(copy.get<std::string>(0) == "cat");

        initial.get<std::string>(0).append("harsis");
        CHECK(copy.get<std::string>(0) == "cat");
    }

    SECTION("The copying assignment of the rtt leads to the creation of real copies of the objects stored in it.") {
        rtt initial(std::vector<std::string>(1, "dog"));

        rtt copy(std::string("qwerty"));
        copy = initial;
        REQUIRE(copy.get<std::vector<std::string>>(0) == std::vector<std::string>(1, "dog"));

        initial.get<std::vector<std::string>>(0).push_back("horse");
        CHECK(copy.get<std::vector<std::string>>(0) == std::vector<std::string>(1, "dog"));
    }

    SECTION("As a result of copy assignment, the volume of the copy is equal to the volume of the original") {
        rtt initial(std::string("cat"), 5, 3.14, std::vector<int>{1, 2});

        rtt copy(true, 2.71);
        copy = initial;
        CHECK(initial.volume() == copy.volume());
    }

    SECTION("As a result of copy assignment, the size of the copy is equal to the size of the original") {
        rtt initial(std::string("cat"), 5, 3.14, std::vector<int>{1, 2});

        rtt copy(17);
        copy = initial;
        CHECK(initial.size() == copy.size());
    }

    SECTION("The result of a copy assignment of an empty rtt is an empty rtt") {
        rtt initial;

        rtt copy(std::string("123"), 'a');
        copy = initial;
        CHECK(copy.empty());
    }

    SECTION("Transferring rtt assignment does not lead to leaks") {
        REQUIRE(dummy::instances_count == 0);
        {
            rtt t(dummy{});
            REQUIRE(dummy::instances_count == 1);

            rtt copy(dummy{});
            REQUIRE(dummy::instances_count == 2);

            copy = std::move(t);
        }
        CHECK(dummy::instances_count == 0);
    }

    SECTION("Knows how to give references to immutable values by their indentation in the rtt") {
        const rtt t(std::string("123"), 42, true);
        auto int_offset = t.offset(1);
        CHECK(t.get_by_offset<int>(int_offset) == 42);
    }

    SECTION("Knows how to give links to mutable values by their indentation in rtt") {
        auto old_value = 42;
        auto new_value = 99;

        rtt t(std::string("123"), old_value, true);
        auto int_offset = t.offset(1);

        REQUIRE(t.get<int>(1) == old_value);
        t.get_by_offset<int>(int_offset) = new_value;

        CHECK(t.get<int>(1) == new_value);
    }

    SECTION("swap") {
        auto t = rtt(1, 3.14);
        auto u = rtt(std::string("qwe"), true);

        swap(t, u);
    }
}
