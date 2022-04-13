#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <actor-zeta.hpp>

using actor_zeta::make_message_id;
using actor_zeta::message_id;

TEST_CASE("default construction") {
    message_id x;
    REQUIRE(x.is_async() == true);
    REQUIRE(x.is_request() == false);
    REQUIRE(x.is_response() == false);
    REQUIRE(x.is_answered() == false);
    REQUIRE(x.priority() == actor_zeta::mailbox::detail::normal_message_priority);
    REQUIRE(x.is_high_message() == false);
    REQUIRE(x.is_normal_message() == true);
    REQUIRE(x == x.response_id());
    REQUIRE(x.request_id().integer_value() == 0u);
    REQUIRE(x.integer_value() == actor_zeta::mailbox::detail::default_async_value);
}

TEST_CASE("make_message_id") {
    auto x = make_message_id();
    message_id y;
    REQUIRE(x == y);
    REQUIRE(x.integer_value() == y.integer_value());
}

TEST_CASE("from integer value") {
    auto x = make_message_id(42);
    REQUIRE(x.is_async() == false);
    REQUIRE(x.is_request() == true);
    REQUIRE(x.is_response() == false);
    REQUIRE(x.is_answered() == false);
    REQUIRE(x.priority() == actor_zeta::mailbox::detail::normal_message_priority);
    REQUIRE(x.is_high_message() == false);
    REQUIRE(x.is_normal_message() == true);
    REQUIRE(x.request_id().integer_value() == 42u);
}

TEST_CASE("response ID") {
    auto x = make_message_id(42).response_id();
    REQUIRE(x.is_async() == false);
    REQUIRE(x.is_request() == false);
    REQUIRE(x.is_response() == true);
    REQUIRE(x.is_answered() == false);
    REQUIRE(x.priority() == actor_zeta::mailbox::detail::normal_message_priority);
    REQUIRE(x.is_high_message() == false);
    REQUIRE(x.is_normal_message() == true);
    REQUIRE(x.request_id().integer_value() == 42u);
}

TEST_CASE("request with high priority") {
    auto x = make_message_id(42).response_id();
    REQUIRE(x.is_async() == false);
    REQUIRE(x.is_request() == false);
    REQUIRE(x.is_response() == true);
    REQUIRE(x.is_answered() == false);
    REQUIRE(x.priority() == actor_zeta::mailbox::detail::normal_message_priority);
    REQUIRE(x.is_high_message() == false);
    REQUIRE(x.is_normal_message() == true);
    REQUIRE(x.request_id().integer_value() == 42u);
}

TEST_CASE("with_priority") {
    auto x = make_message_id();
    REQUIRE(x.priority() == actor_zeta::mailbox::detail::normal_message_priority);
    for (auto category : {actor_zeta::mailbox::detail::high_message_priority,
                          actor_zeta::mailbox::detail::normal_message_priority}) {
        x = x.with_priority(category);
        REQUIRE(x.priority() == category);
        REQUIRE(x.is_request() == false);
        REQUIRE(x.is_response() == false);
        REQUIRE(x.is_answered() == false);
    }
}