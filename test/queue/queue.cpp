#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include <actor-zeta/detail/queue/queue.hpp>

#include "inode.hpp"
#include "fixture.hpp"

namespace tools {

    using queue_type = actor_zeta::detail::queue<inode_policy>;
    using queue_type_pmr = actor_zeta::detail::queue<inode_policy_pmr, allocator_pmr_t>;

    struct fixture
        : public allocator_t
        , public test::fixture<inode_policy, queue_type, inode, allocator_t> {
        fixture()
            : test::fixture<inode_policy, queue_type, inode, allocator_t>(this, policy) {}
    };

    struct fixture_pmr
        : public allocator_pmr_t
        , public test::fixture<inode_policy_pmr, queue_type_pmr, inode, allocator_pmr_t> {
        fixture_pmr(actor_zeta::detail::pmr::memory_resource* mr = nullptr)
            : allocator_pmr_t(mr)
            , test::fixture<inode_policy_pmr, queue_type_pmr, inode, allocator_pmr_t>(this, policy) {}
    };

    auto make_new_round_result(size_t consumed_items, bool stop_all) -> actor_zeta::detail::new_round_result {
        return actor_zeta::detail::new_round_result{consumed_items, stop_all};
    }

} // namespace tools

template<typename Queue_type_t>
auto queue_to_string(Queue_type_t& q) -> std::string {
    std::string str;
    auto peek_fun = [&str, &q](const tools::inode& x) {
        if (!str.empty())
            str += ", ";
        str += std::to_string(x.value);
    };
    q.peek_all(peek_fun);
    return str;
}

#if CPP17_OR_GREATER
TEST_CASE("queue_test pmr") {
    char buffer[256] = {}; // a small buffer on the stack
    std::fill_n(std::begin(buffer), std::size(buffer) - 1, '_');
    std::cout << buffer << '\n';

    actor_zeta::detail::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer)};

    SECTION("default_constructed") {
        tools::fixture_pmr fix(&pool);
        REQUIRE(fix.queue().empty());
        REQUIRE(fix.queue().deficit() == 0);
        REQUIRE(fix.queue().total_task_size() == 0);
        REQUIRE(fix.queue().peek() == nullptr);
        REQUIRE(fix.queue().next() == nullptr);
        REQUIRE(fix.queue().begin() == fix.queue().end());
        std::cout << "default_constructed :: " << buffer << '\n';
    }

    SECTION("inc_deficit") {
        tools::fixture_pmr fix(&pool);
        fix.queue().inc_deficit(100);
        REQUIRE(fix.queue().deficit() == 0);
        fix.fill(1);
        fix.queue().inc_deficit(100);
        REQUIRE(fix.queue().deficit() == 100);
        fix.queue().next();
        REQUIRE(fix.queue().deficit() == 0);
        std::cout << "inc_deficit :: " << buffer << '\n';
    }

    SECTION("new_round") {
        tools::fixture_pmr fix(&pool);
        std::string seq;
        fix.fill(1, 2, 3, 4, 5, 6);
        auto f = [&](tools::inode& x) -> actor_zeta::detail::task_result {
            seq += to_string(x);
            return actor_zeta::detail::task_result::resume;
        };
        auto round_result = fix.queue().new_round(7, f);
        REQUIRE(round_result == tools::make_new_round_result(3, false));
        REQUIRE(seq == "123");
        REQUIRE(fix.queue().deficit() == 1);
        round_result = fix.queue().new_round(8, f);
        REQUIRE(round_result == tools::make_new_round_result(2, false));
        REQUIRE(seq == "12345");
        REQUIRE(fix.queue().deficit() == 0);
        round_result = fix.queue().new_round(1000, f);
        REQUIRE(round_result == tools::make_new_round_result(1, false));
        REQUIRE(seq == "123456");
        REQUIRE(fix.queue().deficit() == 0);
        round_result = fix.queue().new_round(1000, f);
        REQUIRE(round_result == tools::make_new_round_result(0, false));
        REQUIRE(seq == "123456");
        REQUIRE(fix.queue().deficit() == 0);
        std::cout << "new_round :: " << buffer << '\n';
    }

    SECTION("next") {
        tools::fixture_pmr fix(&pool);
        std::string seq;
        fix.fill(1, 2, 3, 4, 5, 6);
        auto f = [&](tools::inode& x) -> actor_zeta::detail::task_result {
            seq += to_string(x);
            return actor_zeta::detail::task_result::resume;
        };
        auto take = [&] {
            fix.queue().flush_cache();
            fix.queue().inc_deficit(fix.queue().peek()->value);
            return fix.queue().next();
        };
        while (!fix.queue().empty()) {
            auto ptr = take();
            f(*ptr);
        }
        REQUIRE(seq == "123456");
        fix.fill(5, 4, 3, 2, 1);
        while (!fix.queue().empty()) {
            auto ptr = take();
            f(*ptr);
        }
        REQUIRE(seq == "12345654321");
        REQUIRE(fix.queue().deficit() == 0);
        std::cout << "next :: " << buffer << '\n';
    }

    SECTION("peek_all") {
        tools::fixture_pmr fix(&pool);
        REQUIRE(queue_to_string(fix.queue()).empty());
        fix.push_back_single(1);
        REQUIRE(queue_to_string(fix.queue()) == "1");
        fix.push_back_single(2);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2");
        fix.push_back_single(3);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
        fix.push_back_single(4);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3, 4");
        std::cout << "peek_all :: " << buffer << '\n';
    }
}
#endif

TEST_CASE("queue_test") {

    SECTION("default_constructed") {
        tools::fixture fix;
        REQUIRE(fix.queue().empty());
        REQUIRE(fix.queue().deficit() == 0);
        REQUIRE(fix.queue().total_task_size() == 0);
        REQUIRE(fix.queue().peek() == nullptr);
        REQUIRE(fix.queue().next() == nullptr);
        REQUIRE(fix.queue().begin() == fix.queue().end());
    }

    SECTION("inc_deficit") {
        tools::fixture fix;
        fix.queue().inc_deficit(100);
        REQUIRE(fix.queue().deficit() == 0);
        fix.fill(1);
        fix.queue().inc_deficit(100);
        REQUIRE(fix.queue().deficit() == 100);
        fix.queue().next();
        REQUIRE(fix.queue().deficit() == 0);
    }

    SECTION("new_round") {
        tools::fixture fix;
        std::string seq;
        fix.fill(1, 2, 3, 4, 5, 6);
        auto f = [&](tools::inode& x) -> actor_zeta::detail::task_result {
            seq += to_string(x);
            return actor_zeta::detail::task_result::resume;
        };
        auto round_result = fix.queue().new_round(7, f);
        REQUIRE(round_result == tools::make_new_round_result(3, false));
        REQUIRE(seq == "123");
        REQUIRE(fix.queue().deficit() == 1);
        round_result = fix.queue().new_round(8, f);
        REQUIRE(round_result == tools::make_new_round_result(2, false));
        REQUIRE(seq == "12345");
        REQUIRE(fix.queue().deficit() == 0);
        round_result = fix.queue().new_round(1000, f);
        REQUIRE(round_result == tools::make_new_round_result(1, false));
        REQUIRE(seq == "123456");
        REQUIRE(fix.queue().deficit() == 0);
        round_result = fix.queue().new_round(1000, f);
        REQUIRE(round_result == tools::make_new_round_result(0, false));
        REQUIRE(seq == "123456");
        REQUIRE(fix.queue().deficit() == 0);
    }

    SECTION("next") {
        tools::fixture fix;
        std::string seq;
        fix.fill(1, 2, 3, 4, 5, 6);
        auto f = [&](tools::inode& x) -> actor_zeta::detail::task_result {
            seq += to_string(x);
            return actor_zeta::detail::task_result::resume;
        };
        auto take = [&] {
            fix.queue().flush_cache();
            fix.queue().inc_deficit(fix.queue().peek()->value);
            return fix.queue().next();
        };
        while (!fix.queue().empty()) {
            auto ptr = take();
            f(*ptr);
        }
        REQUIRE(seq == "123456");
        fix.fill(5, 4, 3, 2, 1);
        while (!fix.queue().empty()) {
            auto ptr = take();
            f(*ptr);
        }
        REQUIRE(seq == "12345654321");
        REQUIRE(fix.queue().deficit() == 0);
    }

    SECTION("peek_all") {
        tools::fixture fix;
        REQUIRE(queue_to_string(fix.queue()).empty());
        fix.push_back_single(1);
        REQUIRE(queue_to_string(fix.queue()) == "1");
        fix.push_back_single(2);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2");
        fix.push_back_single(3);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
        fix.push_back_single(4);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3, 4");
    }
}
