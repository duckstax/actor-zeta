#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

#include <string>

#include <deque>
#include <list>
#include <map>
#include <queue>
#include <vector>

TEST_CASE("message") {
    SECTION("vector of plain messages") {
        std::vector<message> v;
        v.emplace_back(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v.emplace_back(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v.emplace_back(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        REQUIRE(v.size() == 3);
        v.clear();
        v.push_back(message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.push_back(message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.push_back(message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.emplace(v.end(), message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(v.end(), message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(v.end(), message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.insert(v.end(), message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.insert(v.end(), message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.insert(v.end(), message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
    }
    SECTION("list of plain messages") {
        std::list<message> v;
        v.emplace_back(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v.emplace_back(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v.emplace_back(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        REQUIRE(v.size() == 3);
        v.clear();
        v.push_back(message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.push_back(message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.push_back(message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.emplace(v.end(), message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(v.end(), message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(v.end(), message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.insert(v.end(), message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.insert(v.end(), message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.insert(v.end(), message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
    }
    SECTION("map of plain messages") {
        std::map<size_t, message> v;
        v.emplace(0, message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(1, message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(2, message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.emplace(std::make_pair(0, message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        v.emplace(std::make_pair(1, message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        v.emplace(std::make_pair(2, message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.emplace(std::pair{0, message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))});
        v.emplace(std::pair{1, message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))});
        v.emplace(std::pair{2, message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))});
        REQUIRE(v.size() == 3);
        v.clear();
        v.emplace(std::piecewise_construct,
                  std::forward_as_tuple(0),
                  std::forward_as_tuple(message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        v.emplace(std::piecewise_construct,
                  std::forward_as_tuple(1),
                  std::forward_as_tuple(message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        v.emplace(std::piecewise_construct,
                  std::forward_as_tuple(2),
                  std::forward_as_tuple(message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        REQUIRE(v.size() == 3);
        v.clear();
        v[0] = message(address_t::empty_address(), "0", rtt(nullptr, std::string("0"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v[1] = message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v[2] = message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        REQUIRE(v.size() == 3);
        v.clear();
        v.insert(std::make_pair(0, message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        v.insert(std::make_pair(1, message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        v.insert(std::make_pair(2, message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.insert(std::pair{0, message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))});
        v.insert(std::pair{1, message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))});
        v.insert(std::pair{2, message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)))});
        REQUIRE(v.size() == 3);
    }
    SECTION("deque of plain messages") {
        std::deque<message> v;
        v.emplace_back(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v.emplace_back(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        v.emplace_back(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
        REQUIRE(v.size() == 3);
        v.clear();
        v.push_back(message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.push_back(message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.push_back(message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.emplace(v.end(), message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(v.end(), message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.emplace(v.end(), message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
        v.clear();
        v.insert(v.end(), message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.insert(v.end(), message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        v.insert(v.end(), message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
        REQUIRE(v.size() == 3);
    }
    SECTION("queue of plain messages") {
        {
            std::queue<message> v;
            v.emplace(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
            v.emplace(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
            v.emplace(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15)));
            REQUIRE(v.size() == 3);
        }
        {
            std::queue<message> v;
            v.push(message(address_t::empty_address(), "1", rtt(nullptr, std::string("1"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
            v.push(message(address_t::empty_address(), "2", rtt(nullptr, std::string("2"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
            v.push(message(address_t::empty_address(), "3", rtt(nullptr, std::string("3"), static_cast<int>(12), static_cast<int>(14), static_cast<int>(15))));
            REQUIRE(v.size() == 3);
        }
    }
    SECTION("simple") {
        message msg;
        REQUIRE(msg.operator bool() == false);
        message msg_1(address_t::empty_address(), "1", rtt(nullptr, int(1)));
        REQUIRE(msg_1.operator bool() == true);
        REQUIRE(msg_1.command() == "1");
        REQUIRE(msg_1.body().get<int>(0) == 1);
    }
}
