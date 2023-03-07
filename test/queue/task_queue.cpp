#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include <vector>

#include <actor-zeta/detail/queue/task_queue.hpp>

#include "inode.hpp"
#include "fixture.hpp"

namespace tools {

    using queue_type = actor_zeta::detail::task_queue<inode_policy>;

    struct fixture
        : public test::fixture<inode_policy, queue_type, inode> {
        fixture(actor_zeta::detail::pmr::memory_resource* mr = actor_zeta::detail::pmr::get_default_resource())
            : test::fixture<inode_policy, queue_type, inode>(mr, policy) {}
    };

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
TEST_CASE("task_queue_tests pmr") {
    char buffer[256] = {}; // a small buffer on the stack
    std::fill_n(std::begin(buffer), std::size(buffer) - 1, '_');
    std::cout << buffer << '\n';

    actor_zeta::detail::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer)};

    SECTION("default_constructed") {
        tools::fixture fix(&pool);
        REQUIRE(fix.queue().empty());
        REQUIRE(fix.queue().total_task_size() == 0);
        REQUIRE(fix.queue().peek() == nullptr);
        REQUIRE(fix.queue().begin() == fix.queue().end());
        std::cout << "default_constructed :: " << buffer << '\n';
    }

    SECTION("push_back") {
        tools::fixture fix(&pool);
        REQUIRE(queue_to_string(fix.queue()).empty());
        fix.fill(1);
        REQUIRE(queue_to_string(fix.queue()) == "1");
        fix.fill_unique(2);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2");
        fix.fill(3);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
        std::cout << "push_back :: " << buffer << '\n';
    }

    SECTION("lifo_conversion") {
        tools::fixture fix(&pool);
        REQUIRE(queue_to_string(fix.queue()).empty());
        fix.lifo_append(3);
        REQUIRE(queue_to_string(fix.queue()) == "3");
        fix.lifo_append(2);
        fix.lifo_append(1);
        fix.queue().stop_lifo_append();
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
        std::cout << "lifo_conversion :: " << buffer << '\n';
    }

    SECTION("move_construct") {
        tools::fixture fix(&pool);
        fix.fill(1, 2, 3);
        auto q2 = std::move(fix.queue());
        REQUIRE(fix.queue().empty());
        REQUIRE_FALSE(q2.empty());
        REQUIRE(queue_to_string(q2) == "1, 2, 3");
        std::cout << "move_construct :: " << buffer << '\n';
    }

    SECTION("move_assign") {
        tools::fixture fix(&pool);
        auto q2 = fix.duplicate(fix.policy);
        fix.fill_queue(q2, 1, 2, 3);
        fix.queue() = std::move(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue().empty());
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
        std::cout << "move_assign :: " << buffer << '\n';
    }

    SECTION("append") {
        tools::fixture fix(&pool);
        auto q2 = fix.duplicate(fix.policy);
        fix.fill(1, 2, 3);
        fix.fill_queue(q2, 4, 5, 6);
        fix.queue().append(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue().empty());
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3, 4, 5, 6");
        std::cout << "append :: " << buffer << '\n';
    }

    SECTION("prepend") {
        tools::fixture fix(&pool);
        auto q2 = fix.duplicate(fix.policy);
        fix.fill(1, 2, 3);
        fix.fill_queue(q2, 4, 5, 6);
        fix.queue().prepend(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue().empty());
        REQUIRE(queue_to_string(fix.queue()) == "4, 5, 6, 1, 2, 3");
        std::cout << "prepend :: " << buffer << '\n';
    }

    SECTION("peek") {
        tools::fixture fix(&pool);
        REQUIRE(fix.queue().peek() == nullptr);
        fix.fill(1, 2, 3);
        REQUIRE(fix.queue().peek()->value == 1);
        std::cout << "peek :: " << buffer << '\n';
    }

    SECTION("task_size") {
        tools::fixture fix(&pool);
        fix.fill(1, 2, 3);
        REQUIRE(fix.queue().total_task_size() == 6);
        fix.fill(4, 5);
        REQUIRE(fix.queue().total_task_size() == 15);
        fix.queue().clear();
        REQUIRE(fix.queue().total_task_size() == 0);
        std::cout << "task_size :: " << buffer << '\n';
    }
}
#endif

TEST_CASE("task_queue_tests") {
    SECTION("default_constructed") {
        tools::fixture fix;
        REQUIRE(fix.queue().empty());
        REQUIRE(fix.queue().total_task_size() == 0);
        REQUIRE(fix.queue().peek() == nullptr);
        REQUIRE(fix.queue().begin() == fix.queue().end());
    }

    SECTION("push_back") {
        tools::fixture fix;
        REQUIRE(queue_to_string(fix.queue()).empty());
        fix.fill(1);
        REQUIRE(queue_to_string(fix.queue()) == "1");
        fix.fill_unique(2);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2");
        fix.fill(3);
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
    }

    SECTION("lifo_conversion") {
        tools::fixture fix;
        REQUIRE(queue_to_string(fix.queue()).empty());
        fix.lifo_append(3);
        REQUIRE(queue_to_string(fix.queue()) == "3");
        fix.lifo_append(2);
        fix.lifo_append(1);
        fix.queue().stop_lifo_append();
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
    }

    SECTION("move_construct") {
        tools::fixture fix;
        fix.fill(1, 2, 3);
        auto q2 = std::move(fix.queue());
        REQUIRE(fix.queue().empty());
        REQUIRE_FALSE(q2.empty());
        REQUIRE(queue_to_string(q2) == "1, 2, 3");
    }

    SECTION("move_assign") {
        tools::fixture fix;
        auto q2 = fix.duplicate(fix.policy);
        fix.fill_queue(q2, 1, 2, 3);
        fix.queue() = std::move(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue().empty());
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3");
    }

    SECTION("append") {
        tools::fixture fix;
        auto q2 = fix.duplicate(fix.policy);
        fix.fill(1, 2, 3);
        fix.fill_queue(q2, 4, 5, 6);
        fix.queue().append(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue().empty());
        REQUIRE(queue_to_string(fix.queue()) == "1, 2, 3, 4, 5, 6");
    }

    SECTION("prepend") {
        tools::fixture fix;
        auto q2 = fix.duplicate(fix.policy);
        fix.fill(1, 2, 3);
        fix.fill_queue(q2, 4, 5, 6);
        fix.queue().prepend(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue().empty());
        REQUIRE(queue_to_string(fix.queue()) == "4, 5, 6, 1, 2, 3");
    }

    SECTION("peek") {
        tools::fixture fix;
        REQUIRE(fix.queue().peek() == nullptr);
        fix.fill(1, 2, 3);
        REQUIRE(fix.queue().peek()->value == 1);
    }

    SECTION("task_size") {
        tools::fixture fix;
        fix.fill(1, 2, 3);
        REQUIRE(fix.queue().total_task_size() == 6);
        fix.fill(4, 5);
        REQUIRE(fix.queue().total_task_size() == 15);
        fix.queue().clear();
        REQUIRE(fix.queue().total_task_size() == 0);
    }
}
