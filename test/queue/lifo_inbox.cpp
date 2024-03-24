#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include <actor-zeta/detail/queue/lifo_inbox.hpp>
#include <actor-zeta/detail/queue/singly_linked.hpp>

using namespace actor_zeta::detail;

namespace {

    struct inode : singly_linked<inode> {
        int value;
        explicit inode(int x = 0)
            : value(x) {}
    };

    auto to_string(const inode& x) -> std::string {
        return std::to_string(x.value);
    }

    using inbox_type = lifo_inbox<inode>;

    struct fixture {
        inbox_type inbox;

        void fill() {
        }

        template<class T, class... Ts>
        void fill(T x, Ts... xs) {
            inbox.emplace_front(x);
            fill(xs...);
        }

        auto close_and_fetch() -> std::string {
            std::string result;
            auto f = [&](inode* x) {
                result += to_string(*x);
                delete x;
            };
            inbox.close(f);
            return result;
        }
    };

} // namespace

TEST_CASE("lifo_inbox_tests") {
    SECTION("default_constructed") {
        fixture fix;
        REQUIRE(fix.inbox.empty());
    }

    SECTION("push_front") {
        fixture fix;
        fix.fill(1, 2, 3);
        REQUIRE(fix.close_and_fetch() == "321");
        REQUIRE(fix.inbox.closed());
    }

    SECTION("push_after_close") {
        fixture fix;
        fix.inbox.close();
        auto res = fix.inbox.emplace_front(0);
        REQUIRE(res == enqueue_result::queue_closed);
    }

    SECTION("unblock") {
        fixture fix;
        REQUIRE(fix.inbox.try_block());
        auto res = fix.inbox.emplace_front(1);
        REQUIRE(res == enqueue_result::unblocked_reader);
        res = fix.inbox.emplace_front(2);
        REQUIRE(res == enqueue_result::success);
        REQUIRE(fix.close_and_fetch() == "21");
    }
}
