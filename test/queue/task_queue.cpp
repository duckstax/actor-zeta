#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include <vector>

#include <actor-zeta/detail/queue/singly_linked.hpp>
#include <actor-zeta/detail/queue/task_queue.hpp>

using namespace actor_zeta::detail;

namespace {

    struct inode : singly_linked<inode> {
        int value;
        explicit inode(int x = 0)
            : value(x) {}
    };

    inline bool operator==(const inode& lhs, const inode& rhs) {
        return lhs.value == rhs.value;
    }
    inline bool operator!=(const inode& lhs, const inode& rhs) {
        return !operator==(lhs, rhs);
    }

    struct inode_policy {
        using mapped_type = inode;
        using task_size_type = int;
        using deleter_type = std::default_delete<mapped_type>;
        using unique_pointer = std::unique_ptr<mapped_type, deleter_type>;

        static inline auto task_size(const mapped_type& x) -> task_size_type {
            return x.value;
        }
    };

    using queue_type = task_queue<inode_policy>;

    struct fixture {
        inode_policy policy;
        queue_type queue_{policy};

        void fill(queue_type&) {}

        template<class T, class... Ts>
        void fill(queue_type& q, T x, Ts... xs) {
            q.emplace_back(x);
            fill(q, xs...);
        }
    };

} // namespace

TEST_CASE("task_queue_tests") {
    SECTION("default_constructed") {
        fixture fix;
        REQUIRE(fix.queue_.empty());
        REQUIRE(fix.queue_.total_task_size() == 0);
        REQUIRE(fix.queue_.peek() == nullptr);
        REQUIRE(fix.queue_.begin() == fix.queue_.end());
    }

    auto queue_to_string = [](queue_type& q) {
        std::string str;
        auto peek_fun = [&str, &q](const inode& x) {
            if (!str.empty())
                str += ", ";
            str += std::to_string(x.value);
        };
        q.peek_all(peek_fun);
        return str;
    };

    SECTION("push_back") {
        fixture fix;
        REQUIRE(queue_to_string(fix.queue_).empty());
        fix.queue_.emplace_back(1);
        REQUIRE(queue_to_string(fix.queue_) == "1");
        fix.queue_.push_back(inode_policy::unique_pointer{new inode(2)});
        REQUIRE(queue_to_string(fix.queue_) == "1, 2");
        fix.queue_.push_back(new inode(3));
        REQUIRE(queue_to_string(fix.queue_) == "1, 2, 3");
    }

    SECTION("lifo_conversion") {
        fixture fix;
        REQUIRE(queue_to_string(fix.queue_).empty());
        fix.queue_.lifo_append(new inode(3));
        REQUIRE(queue_to_string(fix.queue_) == "3");
        fix.queue_.lifo_append(new inode(2));
        fix.queue_.lifo_append(new inode(1));
        fix.queue_.stop_lifo_append();
        REQUIRE(queue_to_string(fix.queue_) == "1, 2, 3");
    }

    SECTION("move_construct") {
        fixture fix;
        fix.fill(fix.queue_, 1, 2, 3);
        queue_type q2 = std::move(fix.queue_);
        REQUIRE(fix.queue_.empty());
        REQUIRE_FALSE(q2.empty());
        REQUIRE(queue_to_string(q2) == "1, 2, 3");
    }

    SECTION("move_assign") {
        fixture fix;
        queue_type q2{fix.policy};
        fix.fill(q2, 1, 2, 3);
        fix.queue_ = std::move(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue_.empty());
        REQUIRE(queue_to_string(fix.queue_) == "1, 2, 3");
    }

    SECTION("append") {
        fixture fix;
        queue_type q2{fix.policy};
        fix.fill(fix.queue_, 1, 2, 3);
        fix.fill(q2, 4, 5, 6);
        fix.queue_.append(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue_.empty());
        REQUIRE(queue_to_string(fix.queue_) == "1, 2, 3, 4, 5, 6");
    }

    SECTION("prepend") {
        fixture fix;
        queue_type q2{fix.policy};
        fix.fill(fix.queue_, 1, 2, 3);
        fix.fill(q2, 4, 5, 6);
        fix.queue_.prepend(q2);
        REQUIRE(q2.empty());
        REQUIRE_FALSE(fix.queue_.empty());
        REQUIRE(queue_to_string(fix.queue_) == "4, 5, 6, 1, 2, 3");
    }

    SECTION("peek") {
        fixture fix;
        REQUIRE(fix.queue_.peek() == nullptr);
        fix.fill(fix.queue_, 1, 2, 3);
        REQUIRE(fix.queue_.peek()->value == 1);
    }

    SECTION("task_size") {
        fixture fix;
        fix.fill(fix.queue_, 1, 2, 3);
        REQUIRE(fix.queue_.total_task_size() == 6);
        fix.fill(fix.queue_, 4, 5);
        REQUIRE(fix.queue_.total_task_size() == 15);
        fix.queue_.clear();
        REQUIRE(fix.queue_.total_task_size() == 0);
    }
}
