#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include <actor-zeta/detail/queue/lifo_inbox.hpp>
#include <actor-zeta/detail/queue/singly_linked.hpp>

#include "inode.hpp"
#include "fixture.hpp"

using namespace actor_zeta::detail;

namespace tools {

    using queue_type = lifo_inbox<inode_policy>;

    struct fixture
        : public test::fixture<inode_policy, queue_type, inode> {
        actor_zeta::detail::pmr::memory_resource* mr_;
        fixture(actor_zeta::detail::pmr::memory_resource* mr = actor_zeta::detail::pmr::get_default_resource())
            : test::fixture<inode_policy, queue_type, inode>(mr)
            , mr_(mr) {}

        auto fetch() -> std::string {
            std::string result;
            inode_policy::unique_pointer ptr{queue_.take_head(), inode_policy::deleter_type(mr_)};
            while (ptr != nullptr) {
                auto next = ptr->next;
                result += to_string(*ptr);
                ptr.reset(queue_type::promote(next));
            }
            return result;
        }

        auto close_and_fetch() -> std::string {
            std::string result;
            auto f = [&](inode* x) {
                result += to_string(*x);
                inode_policy::deleter_type deleter(mr_);
                deleter(x);
            };
            queue_.close(f);
            return result;
        }
    };

} // namespace tools

#if CPP17_OR_GREATER
TEST_CASE("lifo_inbox_tests pmr") {
    char buffer[256] = {}; // a small buffer on the stack
    std::fill_n(std::begin(buffer), std::size(buffer) - 1, '_');
    std::cout << buffer << '\n';

    actor_zeta::detail::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer)};
    SECTION("default_constructed") {
        tools::fixture fix(&pool);
        REQUIRE(fix.queue_.empty());
    }

    SECTION("push_front") {
        tools::fixture fix(&pool);
        fix.fill_front(1, 2, 3);
        REQUIRE(fix.close_and_fetch() == "321");
        REQUIRE(fix.queue_.closed());
    }

    SECTION("push_after_close") {
        tools::fixture fix(&pool);
        fix.queue_.close();
        auto res = fix.fill_front_single(0);
        REQUIRE(res == enqueue_result::queue_closed);
    }

    SECTION("unblock") {
        tools::fixture fix(&pool);
        REQUIRE(fix.queue_.try_block());
        auto res = fix.fill_front_single(1);
        REQUIRE(res == enqueue_result::unblocked_reader);
        res = fix.fill_front_single(2);
        REQUIRE(res == enqueue_result::success);
        REQUIRE(fix.close_and_fetch() == "21");
    }
}
#endif

TEST_CASE("lifo_inbox_tests") {
    SECTION("default_constructed") {
        tools::fixture fix;
        REQUIRE(fix.queue_.empty());
    }

    SECTION("push_front") {
        tools::fixture fix;
        fix.fill_front(1, 2, 3);
        REQUIRE(fix.close_and_fetch() == "321");
        REQUIRE(fix.queue_.closed());
    }

    SECTION("push_after_close") {
        tools::fixture fix;
        fix.queue_.close();
        auto res = fix.fill_front_single(0);
        REQUIRE(res == enqueue_result::queue_closed);
    }

    SECTION("unblock") {
        tools::fixture fix;
        REQUIRE(fix.queue_.try_block());
        auto res = fix.fill_front_single(1);
        REQUIRE(res == enqueue_result::unblocked_reader);
        res = fix.fill_front_single(2);
        REQUIRE(res == enqueue_result::success);
        REQUIRE(fix.close_and_fetch() == "21");
    }
}
