#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include <actor-zeta/detail/queue/fifo_inbox.hpp>
#include <actor-zeta/detail/queue/queue.hpp>
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

    struct inode_policy {
        using mapped_type = inode;
        using task_size_type = int;
        using deficit_type = int;
        using deleter_type = std::default_delete<mapped_type>;
        using unique_pointer = std::unique_ptr<mapped_type, deleter_type>;
        using queue_type = queue<inode_policy>;

        static constexpr auto task_size(const inode&) noexcept -> task_size_type {
            return 1;
        }
    };

    using inbox_type = fifo_inbox<inode_policy>;

    struct fixture {
        inode_policy policy;
        inbox_type inbox{policy};

        void fill() {}

        template<class T, class... Ts>
        void fill(T x, Ts... xs) {
            inbox.emplace_back(x);
            fill(xs...);
        }

        auto close_and_fetch() -> std::string {
            std::string result;
            auto f = [&](inode& x) -> task_result {
                result += to_string(x);
                return task_result::resume;
            };
            inbox.close();
            inbox.queue().new_round(1000, f);
            return result;
        }
    };

} // namespace

TEST_CASE("fifo_inbox_tests") {
    SECTION("default_constructed") {
        fixture fix;
        REQUIRE(fix.inbox.empty());
    }

    SECTION("push_front") {
        fixture fix;
        fix.fill(1, 2, 3);
        REQUIRE(fix.close_and_fetch() == "123");
        REQUIRE(fix.inbox.closed());
    }

    SECTION("push_after_close") {
        fixture fix;
        fix.inbox.close();
        auto res = fix.inbox.push_back(new inode(0));
        REQUIRE(res == enqueue_result::queue_closed);
    }

    SECTION("unblock") {
        fixture fix;
        REQUIRE(fix.inbox.try_block());
        auto res = fix.inbox.push_back(new inode(0));
        REQUIRE(res == enqueue_result::unblocked_reader);
        res = fix.inbox.push_back(new inode(1));
        REQUIRE(res == enqueue_result::success);
        REQUIRE(fix.close_and_fetch() == "01");
    }
}