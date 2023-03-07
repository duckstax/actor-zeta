#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <actor-zeta/detail/unique_function.hpp>
#include <actor-zeta/mailbox/message.hpp>

using action = actor_zeta::detail::unique_function<void(actor_zeta::mailbox::message*)>;

TEST_CASE("unique_function") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();

    SECTION("ctor enable_if") {

        auto l1 = [](int, int, int) {};
        auto l2 = [](int, int, int) {};

        // test case as in header/actor-zeta/impl/handler.ipp
        REQUIRE(action::test_same_decltype([f = std::move(l1)](actor_zeta::mailbox::message*) -> void {}));
        REQUIRE(action::test_convertible([f = std::move(l2)](actor_zeta::mailbox::message*) -> void {}));
    }
    
    SECTION("ctor") {
        for (int i = 0; i < 1024 * 1024; ++i) {
            auto l1 = [](int, int, int) {};
            action tmp(mr_ptr, [f = std::move(l1)](actor_zeta::mailbox::message*) -> void {});
        }
    }
}

#if CPP17_OR_GREATER
TEST_CASE("unique_function pmr") {
    char buffer[256] = {}; // a small buffer on the stack
    std::fill_n(std::begin(buffer), std::size(buffer) - 1, '_');
    std::cout << buffer << '\n';

    actor_zeta::detail::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer)};

    SECTION("ctor enable_if") {

        auto l1 = [](int, int, int) {};
        auto l2 = [](int, int, int) {};

        // test case as in header/actor-zeta/impl/handler.ipp
        REQUIRE(action::test_same_decltype([f = std::move(l1)](actor_zeta::mailbox::message*) -> void {}));
        REQUIRE(action::test_convertible([f = std::move(l2)](actor_zeta::mailbox::message*) -> void {}));
    }
    
    SECTION("ctor") {
        for (int i = 0; i < 1024 * 1024; ++i) {
            auto l1 = [](int, int, int) {};
            action tmp(&pool, [f = std::move(l1)](actor_zeta::mailbox::message*) -> void {});
        }
    }
}
#endif
