#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("any") {
    {
#if not CPP17_OR_GREATER
        REQUIRE(sizeof(std::string) <= sizeof(any));
        REQUIRE(sizeof(std::vector<int>) <= sizeof(any));
#endif
    }

    SECTION("empty any") {
        any a;
        REQUIRE(!a.has_value());
    }

    SECTION("string any") {
        any a(std::string("test string"));
        REQUIRE(a.has_value());
        REQUIRE(any_cast<std::string>(a) == "test string");
    }

    SECTION("string reset any") {
        any a(std::string("test string"));
        REQUIRE(a.has_value());
        a.reset();
        REQUIRE(!a.has_value());
    }

    SECTION("assignment any") {
        any a1 = 42;
        any a2 = a1;

        REQUIRE(a1.has_value());
        REQUIRE(a2.has_value());
        REQUIRE(any_cast<int>(a1) == any_cast<int>(a2));
    }

    SECTION("big_object any") {
        big_object::reset();
        { any a{big_object()}; }
        REQUIRE(big_object::is_clear());
    }

    SECTION("small_object any") {
        small_object::reset();
        { any a{small_object()}; }
        REQUIRE(small_object::is_clear());
    }

    SECTION("any_cast") {
        any a(42);
        REQUIRE(a.has_value() == true);

        REQUIRE(any_cast<int>(a) == 42);
        REQUIRE(any_cast<int>(a) != 1337);
        any_cast<int&>(a) = 10;
        REQUIRE(any_cast<int>(a) == 10);

        a = 1.f;
        any_cast<float&>(a) = 1337.f;
        REQUIRE(any_cast<float>(a) == 1337.f);

        a = 4343;
        REQUIRE(any_cast<int>(a) == 4343);

        a = std::string("hello world");
        REQUIRE(any_cast<std::string>(a) == "hello world");
        REQUIRE(any_cast<std::string&>(a) == "hello world");
    }

    SECTION("custom_type any") {
        struct custom_type {
            custom_type()
                : data_() {}
            int data_;
        };

        any a = custom_type();
        any_cast<custom_type&>(a).data_ = 42;
        REQUIRE(any_cast<custom_type>(a).data_ == 42);
    }

    SECTION("vector any_cast 1") {
        std::vector<any> va = {42, 'a', 42.f, 3333u, 4444ul, 5555ull, 6666.0};

        REQUIRE(any_cast<int>(va[0]) == 42);
        REQUIRE(any_cast<char>(va[1]) == 'a');
        REQUIRE(any_cast<float>(va[2]) == 42.f);
        REQUIRE(any_cast<unsigned>(va[3]) == 3333u);
        REQUIRE(any_cast<unsigned long>(va[4]) == 4444ul);
        REQUIRE(any_cast<unsigned long long>(va[5]) == 5555ull);
        REQUIRE(any_cast<double>(va[6]) == 6666.0);
    }

    SECTION("vector any_cast 2") {
        std::vector<any> va = {42, std::string("ted"), 'a', 42.f};
        REQUIRE(any_cast<int>(va[0]) == 42);
        REQUIRE(any_cast<std::string>(va[1]) == "ted");
        REQUIRE(any_cast<char>(va[2]) == 'a');
        REQUIRE(any_cast<float>(va[3]) == 42.f);
    }

    SECTION("vector emplace_back any_cast") {
        std::vector<any> va;
        va.emplace_back(42);
        va.emplace_back(std::string("ted"));
        va.emplace_back('a');
        va.emplace_back(42.f);

        REQUIRE(any_cast<int>(va[0]) == 42);
        REQUIRE(any_cast<std::string>(va[1]) == "ted");
        REQUIRE(any_cast<char>(va[2]) == 'a');
        REQUIRE(any_cast<float>(va[3]) == 42.f);
    }

    SECTION("vector and big_object any_cast") {
        big_object::reset();
        {
            std::vector<any> va = {42, 'a', 42.f, 3333u, 4444ul, 5555ull, 6666.0};

            REQUIRE(any_cast<int>(va[0]) == 42);
            REQUIRE(any_cast<char>(va[1]) == 'a');
            REQUIRE(any_cast<float>(va[2]) == 42.f);
            REQUIRE(any_cast<unsigned>(va[3]) == 3333u);
            REQUIRE(any_cast<unsigned long>(va[4]) == 4444ul);
            REQUIRE(any_cast<unsigned long long>(va[5]) == 5555ull);
            REQUIRE(any_cast<double>(va[6]) == 6666.0);

            va[3] = big_object(3333);

            REQUIRE(any_cast<int>(va[0]) == 42);
            REQUIRE(any_cast<char>(va[1]) == 'a');
            REQUIRE(any_cast<float>(va[2]) == 42.f);
            REQUIRE(any_cast<big_object>(va[3]).x_ == 3333);
            REQUIRE(any_cast<unsigned long>(va[4]) == 4444ul);
            REQUIRE(any_cast<unsigned long long>(va[5]) == 5555ull);
            REQUIRE(any_cast<double>(va[6]) == 6666.0);
        }
        REQUIRE(big_object::is_clear());
    }

    SECTION("assignment string any_cast 1") {
        any a1;
        REQUIRE(!a1.has_value());
        {
            any a2(std::string("test string"));
            a1 = any_cast<std::string>(a2);

            REQUIRE(a1.has_value());
        }
        REQUIRE(any_cast<std::string>(a1) == "test string");
        REQUIRE(a1.has_value());
    }

    SECTION("assignment string any_cast 2") {
        any a1;
        REQUIRE(!a1.has_value());
        {
            any a2(std::string("test string"));
            a1 = a2;
            REQUIRE(a1.has_value());
        }
        REQUIRE(any_cast<std::string&>(a1) == "test string");
        REQUIRE(a1.has_value());
    }

    SECTION("int swap any_cast") {
        any a1 = 42;
        any a2 = 24;
        REQUIRE(any_cast<int>(a1) == 42);
        REQUIRE(any_cast<int>(a2) == 24);

        a1.swap(a2);
        REQUIRE(any_cast<int>(a1) == 24);
        REQUIRE(any_cast<int>(a2) == 42);

        std::swap(a1, a2);
        REQUIRE(any_cast<int>(a1) == 42);
        REQUIRE(any_cast<int>(a2) == 24);
    }

    SECTION("string swap any_cast") {
        any a1 = std::string("hello");
        any a2 = std::string("world");
        REQUIRE(any_cast<std::string>(a1) == "hello");
        REQUIRE(any_cast<std::string>(a2) == "world");

        a1.swap(a2);
        REQUIRE(any_cast<std::string>(a1) == "world");
        REQUIRE(any_cast<std::string>(a2) == "hello");

        std::swap(a1, a2);
        REQUIRE(any_cast<std::string>(a1) == "hello");
        REQUIRE(any_cast<std::string>(a2) == "world");
    }

    SECTION("emplace reset any_cast") {
        any a;

        a.emplace<int>(42);
        REQUIRE(a.has_value());
        REQUIRE(any_cast<int>(a) == 42);

        a.emplace<short>(static_cast<short>(8)); // no way to define a short literal we must cast here.
        REQUIRE(any_cast<short>(a) == 8);
        REQUIRE(a.has_value());

        a.reset();
        REQUIRE(!a.has_value());
    }

    SECTION("big_object emplace") {
        big_object::reset();
        {
            any a;
            a.emplace<big_object>();
            REQUIRE(a.has_value());
        }
        REQUIRE(big_object::is_clear());
    }

    SECTION("emplace list any_cast") {
        any a;
        a.emplace<list_of_numbers>(std::initializer_list<int>{1, 2, 3, 4, 5, 6});

        REQUIRE(a.has_value());
        REQUIRE(any_cast<list_of_numbers>(a).sum == 21);
    }

    SECTION("comparison any_cast") {
        any a, b;
        REQUIRE(!a.has_value() == !b.has_value());

        a = 42;
        b = 24;
        REQUIRE(any_cast<int>(a) != any_cast<int>(b));
        REQUIRE(a.has_value() == b.has_value());

        a = 42;
        b = 42;
        REQUIRE(any_cast<int>(a) == any_cast<int>(b));
        REQUIRE(a.has_value() == b.has_value());
    }

    SECTION("string move any_cast") {
        any a = std::string("hello world");
        REQUIRE(any_cast<std::string&>(a) == "hello world");

        auto s = move(any_cast<std::string&>(a));
        REQUIRE(s == "hello world");
        REQUIRE(any_cast<std::string&>(a).empty());

        any_cast<std::string&>(a) = move(s);
        REQUIRE(any_cast<std::string&>(a) == "hello world");
    }

    SECTION("any_cast nullptr") {
        any* a = nullptr;
        REQUIRE(any_cast<int>(a) == nullptr);
        REQUIRE(any_cast<short>(a) == nullptr);
        REQUIRE(any_cast<long>(a) == nullptr);
        REQUIRE(any_cast<std::string>(a) == nullptr);
        ignore_unused(a);

        any b;
        REQUIRE(any_cast<short>(&b) == nullptr);
        REQUIRE(any_cast<const short>(&b) == nullptr);
        REQUIRE(any_cast<volatile short>(&b) == nullptr);
        REQUIRE(any_cast<const volatile short>(&b) == nullptr);

        REQUIRE(any_cast<short*>(&b) == nullptr);
        REQUIRE(any_cast<const short*>(&b) == nullptr);
        REQUIRE(any_cast<volatile short*>(&b) == nullptr);
        REQUIRE(any_cast<const volatile short*>(&b) == nullptr);
    }

    SECTION("make_any any_cast") {
        auto a = make_any<int>(42);
        REQUIRE(any_cast<int>(a) == 42);
    }

    SECTION("make_any list any_cast") {
        auto a = make_any<list_of_numbers>(std::initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8});
        REQUIRE(any_cast<list_of_numbers&>(a).sum == 36);
    }

    SECTION("float any_cast") {
        float f = 42.f;
        any a(f);
        REQUIRE(any_cast<float>(a) == 42.f);
    }

    SECTION("rawptr any_cast") {
        any a = 1;
        int* i = any_cast<int>(&a);
        REQUIRE((*i) == 1);
    }

    SECTION("empty any has_value") {
        any a1;
        any a2;
        REQUIRE(a1.has_value() == false);
        REQUIRE(a2.has_value() == false);

        a1 = a2;
        REQUIRE(a1.has_value() == false);
        REQUIRE(a2.has_value() == false);
    }

    SECTION("any has_value") {
        any a1 = 42;
        any a2;
        REQUIRE(a1.has_value() == true);
        REQUIRE(a2.has_value() == false);

        a1 = a2;
        REQUIRE(a1.has_value() == false);
        REQUIRE(a2.has_value() == false);
    }

    SECTION("has_value any_cast assignment") {
        any a1;
        any a2 = 42;
        REQUIRE(a1.has_value() == false);
        REQUIRE(a2.has_value() == true);

        a1 = a2;
        REQUIRE(a1.has_value() == true);
        REQUIRE(a2.has_value() == true);
        REQUIRE(any_cast<int>(a1) == 42);
        REQUIRE(any_cast<int>(a2) == 42);
    }
}
