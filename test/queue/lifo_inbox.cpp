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

    struct inode_policy {
        using mapped_type = inode;
        using task_size_type = int;
        using deficit_type = int;
        using deleter_type = actor_zeta::detail::pmr::deleter_t;
        using unique_pointer = std::unique_ptr<mapped_type, deleter_type>;
    };

    using inbox_type = lifo_inbox<inode_policy>;

    struct fixture final : protected actor_zeta::detail::pmr::memory_resource_base {
        inode_policy policy;
        inbox_type inbox;

        fixture(actor_zeta::detail::pmr::memory_resource* memory_resource)
            : actor_zeta::detail::pmr::memory_resource_base(memory_resource)
            , inbox(resource()) {}

        void fill() {
        }

        template<class T, class... Ts>
        void fill(T x, Ts... xs) {
            inbox.emplace_front(x);
            fill(xs...);
        }

        auto fetch() -> std::string {
            std::string result;
            inode_policy::unique_pointer ptr{inbox.take_head(), actor_zeta::detail::pmr::deleter_t(resource())};
            while (ptr != nullptr) {
                auto next = ptr->next;
                result += to_string(*ptr);
                ptr.reset(inbox_type::promote(next));
            }
            return result;
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
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    SECTION("default_constructed") {
        fixture fix(mr_ptr);
        REQUIRE(fix.inbox.empty());
    }

    SECTION("push_front") {
        fixture fix(mr_ptr);
        fix.fill(1, 2, 3);
        REQUIRE(fix.close_and_fetch() == "321");
        REQUIRE(fix.inbox.closed());
    }

    SECTION("push_after_close") {
        fixture fix(mr_ptr);
        fix.inbox.close();
        auto res = fix.inbox.push_front(actor_zeta::detail::pmr::allocate_ptr<inode>(mr_ptr, 0));
        REQUIRE(res == enqueue_result::queue_closed);
    }

    SECTION("unblock") {
        fixture fix(mr_ptr);
        REQUIRE(fix.inbox.try_block());
        auto res = fix.inbox.push_front(actor_zeta::detail::pmr::allocate_ptr<inode>(mr_ptr, 1));
        REQUIRE(res == enqueue_result::unblocked_reader);
        res = fix.inbox.push_front(actor_zeta::detail::pmr::allocate_ptr<inode>(mr_ptr, 2));
        REQUIRE(res == enqueue_result::success);
        REQUIRE(fix.close_and_fetch() == "21");
    }
}
