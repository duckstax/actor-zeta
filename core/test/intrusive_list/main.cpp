#include <algorithm>
#include <functional>
#include <actor-zeta/detail/intrusive_list.hpp>
#include <actor-zeta/environment/adjacency_list.hpp>

class IntegerListNode {
public:
    IntegerListNode(int value) : node(), value_(value) {}

    // Older versions of Visual Studio don't generate move constructors or move
    // assignment operators.
    IntegerListNode(IntegerListNode &&other) { *this = std::move(other); }

    IntegerListNode &operator=(IntegerListNode &&other) {
        value_ = other.value_;
        node = std::move(other.node);
        return *this;
    }

    int value() const { return value_; }

    actor_zeta::intrusive_list_node node;

private:
    int value_;

    // Disallow copying.
    IntegerListNode(IntegerListNode &);

    IntegerListNode &operator=(IntegerListNode &);
};

bool IntegerListNodeComparitor(const IntegerListNode &a, const IntegerListNode &b) {
    return a.value() < b.value();
}

bool operator<(const IntegerListNode &a, const IntegerListNode &b) {
    return a.value() < b.value();
}

bool operator==(const IntegerListNode &a, const IntegerListNode &b) {
    return a.value() == b.value();
}

class intrusive_list_test:actor_zeta::intrusive_forward_list<IntegerListNode> {
public:
    intrusive_list_test()
            : list_(&IntegerListNode::node),
              one_(1),
              two_(2),
              three_(3),
              four_(4),
              five_(5),
              six_(6),
              seven_(7),
              eight_(8),
              nine_(9),
              ten_(10),
              twenty_(20),
              thirty_(30),
              fourty_(40),
              fifty_(50) {}

    actor_zeta::intrusive_forward_list<IntegerListNode> list_;
    IntegerListNode one_;
    IntegerListNode two_;
    IntegerListNode three_;
    IntegerListNode four_;
    IntegerListNode five_;
    IntegerListNode six_;
    IntegerListNode seven_;
    IntegerListNode eight_;
    IntegerListNode nine_;
    IntegerListNode ten_;
    IntegerListNode twenty_;
    IntegerListNode thirty_;
    IntegerListNode fourty_;
    IntegerListNode fifty_;
};

void intrusive_list_test_push_back() {

    actor_zeta::intrusive_forward_list<IntegerListNode> list_(&IntegerListNode::node);

    assert(!one_.node.in_list());
    assert(!two_.node.in_list());
    assert(!three_.node.in_list());
    assert(!four_.node.in_list());
    assert(!five_.node.in_list());

    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    assert(one_.node.in_list());
    assert(two_.node.in_list());
    assert(three_.node.in_list());
    assert(four_.node.in_list());
    assert(five_.node.in_list());

    auto iter = list_.begin();
    assert(1 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(4 == iter->value());
    ++iter;
    assert(5 == iter->value());
    ++iter;
    assert(list_.end() == iter);

    assert(1 == list_.front().value());
    assert(5 == list_.back().value());
}

void intrusive_list_test_push_back_failure() {
    intrusive_list_test list_;
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);
    assert(list_.push_back(five_) == ".");
}


void intrusive_list_test_pop_back() {
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    assert(5 == list_.back().value());
    list_.pop_back();
    assert(4 == list_.back().value());
    list_.pop_back();
    assert(3 == list_.back().value());
    list_.pop_back();
    list_.push_back(four_);
    assert(4 == list_.back().value());
}

void intrusive_list_test_push_front() {
    list_.push_front(one_);
    list_.push_front(two_);
    list_.push_front(three_);
    list_.push_front(four_);
    list_.push_front(five_);

    auto iter = list_.begin();
    assert(5 == iter->value());
    ++iter;
    assert(4 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(1 == iter->value());
    ++iter;
    assert(list_.end() == iter);

    assert(5 == list_.front().value());
    assert(1 == list_.back().value());
}


void intrusive_list_test_push_front_failure() {
    list_.push_front(five_);
    list_.push_front(four_);
    list_.push_front(three_);
    list_.push_front(two_);
    list_.push_front(one_);
    assert(list_.push_front(one_) == ".");
}


void intrusive_list_test_destructor() {
    list_.push_back(one_);
    list_.push_back(two_);
    {
// These should remove themselves when they go out of scope.
        IntegerListNode one_hundred(100);
        IntegerListNode two_hundred(200);
        list_.push_back(one_hundred);
        list_.push_back(two_hundred);
    }
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    auto iter = list_.begin();
    assert(1 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(4 == iter->value());
    ++iter;
    assert(5 == iter->value());
    ++iter;
    assert(list_.end() == iter);

    assert(1 == list_.front().value());
    assert(5 == list_.back().value());
}

void intrusive_list_test_move_node() {
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    two_.node = std::move(four_.node);

    auto iter = list_.begin();
    assert(1 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(5 == iter->value());
    ++iter;
    assert(list_.end() == iter);
}

void intrusive_list_test_erase() {
    assert(list_.empty());

    list_.push_back(one_);
    list_.push_back(two_);
    assert(1 == list_.begin()->value());
    list_.erase(list_.begin());
    assert(2 == list_.begin()->value());
    assert(1 == list_.size());

    list_.push_back(one_);
    list_.erase(list_.begin(), list_.end());
    assert(list_.empty());
    assert(0 == list_.size());

    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    auto begin = list_.begin();
    auto end = --list_.end();
    assert(3 == end->value());
    list_.erase(begin, end);
    assert(3 == list_.begin()->value());
    assert(1 == list_.size());
}

void intrusive_list_test_clear() {
    assert(list_.empty());
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);
    assert(list_.empty() == false );
    list_.clear();
    assert(list_.empty());
}

void intrusive_list_test_size() {
    assert(0u == list_.size());
    assert(list_.empty());
    list_.push_back(one_);
    assert(1u == list_.size());
    assert(list_.empty() == false );
    list_.push_back(two_);
    assert(2u == list_.size());
    assert(list_.empty() == false );
    list_.push_front(three_);
    assert(3u == list_.size());
    assert(list_.empty() == false );
    list_.push_back(four_);
    assert(4u == list_.size());
    assert(list_.empty() == false );
    list_.push_front(five_);
    assert(5u == list_.size());
    assert(list_.empty() == false );
    list_.pop_front();
    assert(4u == list_.size());
    assert(list_.empty() == false );
    list_.pop_back();
    assert(3u == list_.size());
    assert(list_.empty() == false );
    list_.pop_front();
    assert(2u == list_.size());
    assert(list_.empty() == false );
    list_.pop_back();
    assert(1u == list_.size());
    assert(list_.empty() == false );
    list_.pop_front();
    assert(0u == list_.size());
    assert(list_.empty());
}

void intrusive_list_test_move_constructor() {
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    fplutil::intrusive_list <IntegerListNode> other(std::move(list_));

    assert(one_.node.in_list());
    assert(two_.node.in_list());
    assert(three_.node.in_list());
    assert(four_.node.in_list());
    assert(five_.node.in_list());

    auto iter = other.begin();
    assert(1 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(4 == iter->value());
    ++iter;
    assert(5 == iter->value());
    ++iter;
    assert(other.end() == iter);
}

void intrusive_list_test_move_assignment() {
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    fplutil::intrusive_list <IntegerListNode> other(&IntegerListNode::node);
    other = std::move(list_);

    assert(one_.node.in_list());
    assert(two_.node.in_list());
    assert(three_.node.in_list());
    assert(four_.node.in_list());
    assert(five_.node.in_list());

    auto iter = other.begin();
    assert(1 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(4 == iter->value());
    ++iter;
    assert(5 == iter->value());
    ++iter;
    assert(other.end() == iter);
}

void intrusive_list_test_swap() {
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    fplutil::intrusive_list <IntegerListNode> other(&IntegerListNode::node);
    other.push_back(ten_);
    other.push_back(twenty_);
    other.push_back(thirty_);
    other.push_back(fourty_);
    other.push_back(fifty_);

    list_.swap(other);

    auto iter = list_.begin();
    assert(10 == iter->value());
    ++iter;
    assert(20 == iter->value());
    ++iter;
    assert(30 == iter->value());
    ++iter;
    assert(40 == iter->value());
    ++iter;
    assert(50 == iter->value());
    ++iter;
    assert(list_.end() == iter);

    iter = other.begin();
    assert(1 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(4 == iter->value());
    ++iter;
    assert(5 == iter->value());
    ++iter;
    assert(other.end() == iter);
}

void intrusive_list_test_swap_self() {
    list_.push_back(one_);
    list_.push_back(two_);
    list_.push_back(three_);
    list_.push_back(four_);
    list_.push_back(five_);

    list_.swap(list_);

    auto iter = list_.begin();
    assert(1 == iter->value());
    ++iter;
    assert(2 == iter->value());
    ++iter;
    assert(3 == iter->value());
    ++iter;
    assert(4 == iter->value());
    ++iter;
    assert(5 == iter->value());
    ++iter;
    assert(list_.end() == iter);
}

int main(int argc, char **argv) {
    intrusive_list_test_push_back();
    intrusive_list_test_push_back_failure();
    intrusive_list_test_pop_back();
    intrusive_list_test_push_front();
    intrusive_list_test_push_front_failure();
    intrusive_list_test_destructor();
    intrusive_list_test_move_node();
    intrusive_list_test_erase();
    intrusive_list_test_clear();
    intrusive_list_test_size();
    intrusive_list_test_move_constructor();
    intrusive_list_test_move_assignment();
    intrusive_list_test_swap();
    intrusive_list_test_swap_self();
    return 0;
}