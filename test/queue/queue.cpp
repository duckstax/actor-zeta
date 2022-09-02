#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

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

        static inline auto task_size(const mapped_type& x) -> task_size_type {
            return x.value;
        }
    };

    using queue_type = queue<inode_policy>;

    struct fixture {
        inode_policy policy;
        queue_type queue_{policy};

        void fill() {}

        template<class T, class... Ts>
        void fill(T x, Ts... xs) {
            queue_.emplace_back(x);
            fill(xs...);
        }
    };

    auto make_new_round_result(size_t consumed_items, bool stop_all) -> new_round_result {
        return new_round_result{consumed_items, stop_all};
    }

} // namespace

TEST_CASE("queue_test") {
    SECTION("default_constructed") {
        fixture fix;
        REQUIRE(fix.queue_.empty());
        REQUIRE(fix.queue_.deficit() == 0);
        REQUIRE(fix.queue_.total_task_size() == 0);
        REQUIRE(fix.queue_.peek() == nullptr);
        REQUIRE(fix.queue_.next() == nullptr);
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

    SECTION("inc_deficit") {
        fixture fix;
        fix.queue_.inc_deficit(100);
        REQUIRE(fix.queue_.deficit() == 0);
        fix.fill(1);
        fix.queue_.inc_deficit(100);
        REQUIRE(fix.queue_.deficit() == 100);
        fix.queue_.next();
        REQUIRE(fix.queue_.deficit() == 0);
    }

    SECTION("new_round") {
        fixture fix;
        std::string seq;
        fix.fill(1, 2, 3, 4, 5, 6);
        auto f = [&](inode& x) -> task_result {
            seq += to_string(x);
            return task_result::resume;
        };
        auto round_result = fix.queue_.new_round(7, f);
        REQUIRE(round_result == make_new_round_result(3, false));
        REQUIRE(seq == "123");
        REQUIRE(fix.queue_.deficit() == 1);
        round_result = fix.queue_.new_round(8, f);
        REQUIRE(round_result == make_new_round_result(2, false));
        REQUIRE(seq == "12345");
        REQUIRE(fix.queue_.deficit() == 0);
        round_result = fix.queue_.new_round(1000, f);
        REQUIRE(round_result == make_new_round_result(1, false));
        REQUIRE(seq == "123456");
        REQUIRE(fix.queue_.deficit() == 0);
        round_result = fix.queue_.new_round(1000, f);
        REQUIRE(round_result == make_new_round_result(0, false));
        REQUIRE(seq == "123456");
        REQUIRE(fix.queue_.deficit() == 0);
    }

    SECTION("next") {
        fixture fix;
        std::string seq;
        fix.fill(1, 2, 3, 4, 5, 6);
        auto f = [&](inode& x) -> task_result {
            seq += to_string(x);
            return task_result::resume;
        };
        auto take = [&] {
            fix.queue_.flush_cache();
            fix.queue_.inc_deficit(fix.queue_.peek()->value);
            return fix.queue_.next();
        };
        while (!fix.queue_.empty()) {
            auto ptr = take();
            f(*ptr);
        }
        REQUIRE(seq == "123456");
        fix.fill(5, 4, 3, 2, 1);
        while (!fix.queue_.empty()) {
            auto ptr = take();
            f(*ptr);
        }
        REQUIRE(seq == "12345654321");
        REQUIRE(fix.queue_.deficit() == 0);
    }

    SECTION("peek_all") {
        fixture fix;
        REQUIRE(queue_to_string(fix.queue_).empty());
        fix.queue_.emplace_back(1);
        REQUIRE(queue_to_string(fix.queue_) == "1");
        fix.queue_.emplace_back(2);
        REQUIRE(queue_to_string(fix.queue_) == "1, 2");
        fix.queue_.emplace_back(3);
        REQUIRE(queue_to_string(fix.queue_) == "1, 2, 3");
        fix.queue_.emplace_back(4);
        REQUIRE(queue_to_string(fix.queue_) == "1, 2, 3, 4");
    }
}
