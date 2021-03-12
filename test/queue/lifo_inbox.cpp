#define CAF_SUITE intrusive.lifo_inbox

#include "caf/intrusive/lifo_inbox.hpp"

#include "caf/test/unit_test.hpp"

#include <memory>

#include "caf/intrusive/singly_linked.hpp"

using namespace caf;
using namespace caf::intrusive;

namespace {

struct inode : singly_linked<inode> {
  int value;
  inode(int x = 0) : value(x) {
    // nop
  }
};

std::string to_string(const inode& x) {
  return std::to_string(x.value);
}

struct inode_policy {
  using mapped_type = inode;

  using task_size_type = int;

  using deficit_type = int;

  using deleter_type = std::default_delete<mapped_type>;

  using unique_pointer = std::unique_ptr<mapped_type, deleter_type>;
};

using inbox_type = lifo_inbox<inode_policy>;

struct fixture {
  inode_policy policy;
  inbox_type inbox;

  void fill(inbox_type&) {
    // nop
  }

  template <class T, class... Ts>
  void fill(inbox_type& i, T x, Ts... xs) {
    i.emplace_front(x);
    fill(i, xs...);
  }

  std::string fetch() {
    std::string result;
    inode_policy::unique_pointer ptr{inbox.take_head()};
    while (ptr != nullptr) {
      auto next = ptr->next;
      result += to_string(*ptr);
      ptr.reset(inbox_type::promote(next));
    }
    return result;
  }

  std::string close_and_fetch() {
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

CAF_TEST_FIXTURE_SCOPE(lifo_inbox_tests, fixture)

CAF_TEST(default_constructed) {
  CAF_REQUIRE_EQUAL(inbox.empty(), true);
}

CAF_TEST(push_front) {
  fill(inbox, 1, 2, 3);
  CAF_REQUIRE_EQUAL(close_and_fetch(), "321");
  CAF_REQUIRE_EQUAL(inbox.closed(), true);
}

CAF_TEST(push_after_close) {
  inbox.close();
  auto res = inbox.push_front(new inode(0));
  CAF_REQUIRE_EQUAL(res, inbox_result::queue_closed);
}

CAF_TEST(unblock) {
  CAF_REQUIRE_EQUAL(inbox.try_block(), true);
  auto res = inbox.push_front(new inode(1));
  CAF_REQUIRE_EQUAL(res, inbox_result::unblocked_reader);
  res = inbox.push_front(new inode(2));
  CAF_REQUIRE_EQUAL(res, inbox_result::success);
  CAF_REQUIRE_EQUAL(close_and_fetch(), "21");
}

CAF_TEST_FIXTURE_SCOPE_END()
