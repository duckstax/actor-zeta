#include <catch2/catch.hpp>

#include <actor-zeta/detail/queue/singly_linked.hpp>
#include <actor-zeta/detail/queue/cached_queue.hpp>

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

        static inline auto task_size(const mapped_type&) noexcept -> task_size_type {
            return 1;
        }
    };

    using queue_type = cached_queue<inode_policy>;

    struct fixture {
        inode_policy policy;
        queue_type queue_{policy};

        void fill() {}

        template <class T, class... Ts>
        void fill(T x, Ts... xs) {
            queue_.emplace_back(x);
            fill(xs...);
        }
    };

    auto make_new_round_result(size_t consumed_items, bool stop_all) -> new_round_result {
        return new_round_result{consumed_items, stop_all};
    }

} //namespace


TEST_CASE("cached_queue_tests") {

    SECTION("default_constructed") {
        fixture fix;
        REQUIRE(fix.queue_.empty());
        REQUIRE(fix.queue_.deficit() == 0);
        REQUIRE(fix.queue_.total_task_size() == 0);
        REQUIRE(fix.queue_.peek() == nullptr);
    }

    SECTION("new_round") {
        std::string fseq;
        auto f = [&](inode& x) -> task_result {
            if ((x.value & 0x01) == 1) {
                return task_result::skip;
            }
            fseq += to_string(x);
            return task_result::resume;
        };
        std::string gseq;
        auto g = [&](inode& x) -> task_result {
            if ((x.value & 0x01) == 0) {
                return task_result::skip;
            }
            gseq += to_string(x);
            return task_result::resume;
        };
        fixture fix;
        fix.fill(1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto round_result = fix.queue_.new_round(3, f);
        REQUIRE(round_result == make_new_round_result(3, false));
        REQUIRE(fseq == "246");
        REQUIRE(fix.queue_.deficit() == 0);
        round_result = fix.queue_.new_round(4, g);
        REQUIRE(round_result == make_new_round_result(4, false));
        REQUIRE(gseq == "1357");
        REQUIRE(fix.queue_.deficit() == 0);
    }

    SECTION("skipping") {
        std::string seq;
        auto f = [&](inode& x) -> task_result {
            if ((x.value & 0x01) == 1) {
                return task_result::skip;
            }
            seq += to_string(x);
            return task_result::resume;
        };
        fixture fix;
        REQUIRE(fix.queue_.new_round(10, f) == make_new_round_result(0, false));
        fix.fill(1, 3, 5);
        REQUIRE(fix.queue_.new_round(10, f) == make_new_round_result(0, false));
        fix.fill(2);
        REQUIRE(fix.queue_.new_round(10, f) == make_new_round_result(1, false));
        REQUIRE(seq == "2");
        fix.fill(7, 9, 4, 11, 13);
        REQUIRE(fix.queue_.new_round(10, f) == make_new_round_result(1, false));
        REQUIRE(seq == "24");
        fix.fill(15, 17, 6);
        REQUIRE(fix.queue_.new_round(10, f) == make_new_round_result(1, false));
        REQUIRE(seq == "246");
    }

    SECTION("take_front") {
        fixture fix;
        std::string seq;
        fix.fill(1, 2, 3, 4, 5, 6);
        auto f = [&](inode& x) -> task_result {
            seq += to_string(x);
            return task_result::resume;
        };
        REQUIRE(fix.queue_.deficit() == 0);
        while (!fix.queue_.empty()) {
            auto ptr = fix.queue_.take_front();
            f(*ptr);
        }
        REQUIRE(seq == "123456");
        fix.fill(5, 4, 3, 2, 1);
        while (!fix.queue_.empty()) {
            auto ptr = fix.queue_.take_front();
            f(*ptr);
        }
        REQUIRE(seq == "12345654321");
        REQUIRE(fix.queue_.deficit() == 0);
    }

    SECTION("alternating_consumer") {
        fixture fix;
        using fun_type = std::function<task_result(inode&)>;
        fun_type f;
        fun_type g;
        fun_type* selected = &f;
        std::string seq;
        f = [&](inode& x) -> task_result {
            if ((x.value & 0x01) == 1) {
                return task_result::skip;
            }
            seq += to_string(x);
            selected = &g;
            return task_result::resume;
        };
        g = [&](inode& x) -> task_result {
            if ((x.value & 0x01) == 0)
            return task_result::skip;
            seq += to_string(x);
            selected = &f;
            return task_result::resume;
        };
        auto h = [&](inode& x) -> task_result {
            return (*selected)(x);
        };
        fix.fill(1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto round_result = fix.queue_.new_round(1000, h);
        REQUIRE(round_result == make_new_round_result(8, false));
        REQUIRE(seq == "21436587");
        REQUIRE(fix.queue_.deficit() == 0);
        //REQUIRE(deep_to_string(queue_.cache()) == "[9]");
    }

    SECTION("peek_all") {
        fixture fix;
        auto queue_to_string = [&] {
            std::string str;
            auto peek_fun = [&](const inode& x) {
                if (!str.empty()) {
                    str += ", ";
                }
                str += std::to_string(x.value);
            };
            fix.queue_.peek_all(peek_fun);
            return str;
        };
        REQUIRE(queue_to_string().empty());
        fix.queue_.emplace_back(2);
        REQUIRE(queue_to_string() == "2");
        fix.queue_.cache().emplace_back(1);
        REQUIRE(queue_to_string() == "2");
        fix.queue_.emplace_back(3);
        REQUIRE(queue_to_string() == "2, 3");
        fix.queue_.flush_cache();
        REQUIRE(queue_to_string() == "1, 2, 3");
    }

}
