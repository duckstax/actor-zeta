#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include <actor-zeta/detail/queue/fixed_queue.hpp>
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

    class high_priority_queue;

    struct inode_policy {
        using mapped_type = inode;
        using task_size_type = int;
        using deficit_type = int;
        using deleter_type = actor_zeta::detail::pmr::deleter_t;
        using unique_pointer = std::unique_ptr<mapped_type, deleter_type>;

        static inline auto task_size(const mapped_type&) -> task_size_type {
            return 1;
        }

        static inline auto id_of(const inode& x) -> size_t {
            return static_cast<size_t>(x.value % 3);
        }

        template<class Queue>
        auto quantum(const Queue&, deficit_type x) const -> deficit_type {
            return x;
        }

        auto quantum(const high_priority_queue&, deficit_type x) const -> deficit_type {
            return enable_priorities ? 2 * x : x;
        }

        bool enable_priorities = false;
    };

    class high_priority_queue : public queue<inode_policy> {
    public:
        using super = queue<inode_policy>;
        using super::super;
    };

    using nested_queue_type = queue<inode_policy>;
    using queue_type = fixed_queue<inode_policy, high_priority_queue, nested_queue_type, nested_queue_type>;

    struct fetch_helper {
        std::string result;

        template<size_t I, class Queue>
        auto operator()(std::integral_constant<size_t, I>, const Queue&, inode& x) -> task_result {
            if (!result.empty()) {
                result += ',';
            }
            result += std::to_string(I);
            result += ':';
            result += to_string(x);
            return task_result::resume;
        }
    };

    struct fixture {
        inode_policy policy;
        queue_type queue_;

        fixture(actor_zeta::detail::pmr::memory_resource* memory_resource)
            : queue_(
                memory_resource,
                policy,
                high_priority_queue(memory_resource, policy),
                nested_queue_type(memory_resource, policy),
                nested_queue_type(memory_resource, policy)) {}

        void fill() {}

        template<class T, class... Ts>
        void fill(T x, Ts... xs) {
            queue_.emplace_back(x);
            fill(xs...);
        }

        auto fetch(int quantum) -> std::string {
            std::string result;
            auto f = [&](size_t id, queue<inode_policy>&, inode& x) -> task_result {
                if (!result.empty()) {
                    result += ',';
                }
                result += std::to_string(id);
                result += ':';
                result += to_string(x);
                return task_result::resume;
            };
            queue_.new_round(quantum, f);
            return result;
        }
    };

    auto make_new_round_result(size_t consumed_items, bool stop_all) -> new_round_result {
        return new_round_result{consumed_items, stop_all};
    }

} // namespace

TEST_CASE("fixed_queue_tests") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    SECTION("default_constructed") {
        fixture fix(mr_ptr);
        REQUIRE(fix.queue_.empty());
    }

    SECTION("new_round") {
        fixture fix(mr_ptr);
        fix.fill(1, 2, 3, 4, 5, 6, 7, 8, 9, 12);
        fetch_helper f;
        auto round_result = fix.queue_.new_round(2, f);
        REQUIRE(round_result == make_new_round_result(6, false));
        REQUIRE(f.result == "0:3,0:6,1:1,1:4,2:2,2:5");
        REQUIRE_FALSE(fix.queue_.empty());
        f.result.clear();
        round_result = fix.queue_.new_round(1, f);
        REQUIRE(round_result == make_new_round_result(3, false));
        REQUIRE(f.result == "0:9,1:7,2:8");
        REQUIRE_FALSE(fix.queue_.empty());
        f.result.clear();
        round_result = fix.queue_.new_round(1000, f);
        REQUIRE(round_result == make_new_round_result(1, false));
        REQUIRE(f.result == "0:12");
        REQUIRE(fix.queue_.empty());
    }

    SECTION("priorities") {
        fixture fix(mr_ptr);
        fix.queue_.policy().enable_priorities = true;
        fix.fill(1, 2, 3, 4, 5, 6, 7, 8, 9);
        REQUIRE(fix.fetch(1) == "0:3,0:6,1:1,2:2");
        REQUIRE_FALSE(fix.queue_.empty());
        REQUIRE(fix.fetch(1) == "0:9,1:4,2:5");
        REQUIRE_FALSE(fix.queue_.empty());
        REQUIRE(fix.fetch(1000) == "1:7,2:8");
        REQUIRE(fix.queue_.empty());
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

    SECTION("peek_all") {
        fixture fix(mr_ptr);
        REQUIRE(queue_to_string(fix.queue_).empty());
        fix.queue_.emplace_back(1);
        REQUIRE(queue_to_string(fix.queue_) == "1");
        fix.queue_.emplace_back(2);
        REQUIRE(queue_to_string(fix.queue_) == "1, 2");
        fix.queue_.emplace_back(3);
        REQUIRE(queue_to_string(fix.queue_) == "3, 1, 2");
        fix.queue_.emplace_back(4);
        REQUIRE(queue_to_string(fix.queue_) == "3, 1, 4, 2");
    }
}
