
#include <cassert>
#include "actor-zeta/intrusive_list.hpp"


struct test_list_item final {
    int dummy;
    actor_zeta::intrusive_list_node link;
};

int main() {
    test_list_item b1, b2, b3;

    using test_list_type = actor_zeta::intrusive_list<test_list_item, &test_list_item::link>;

    test_list_type the_list;
    assert(the_list.empty());

    /// single item basic operations
    {
        the_list.push_front(&b1);
        assert(not the_list.empty());
        assert(the_list.front() == &b1);
        assert(the_list.back() == &b1);
        assert(the_list.is_head(&b1));
        assert(the_list.is_tail(&b1));
        assert(the_list.pop_back() == &b1);
        assert(the_list.empty());
        the_list.push_back(&b1);
        assert(the_list.back() == &b1);
        assert(the_list.front() == &b1);
        assert(the_list.is_head(&b1));
        assert(the_list.is_tail(&b1));
        assert(the_list.pop_front() == &b1);
        assert(the_list.empty());
    }

    /// multiple item operations
    {

        the_list.push_front(&b1);
        the_list.push_front(&b2);
        the_list.push_back(&b3);
        assert(not the_list.empty());
        assert(the_list.front() == &b2);
        assert(the_list.back() == &b3);
        assert(the_list.is_head(&b2));
        assert(the_list.is_tail(&b3));
    }

    /// remove one item
    {
        test_list_type::unlink(&b1);
        assert(not the_list.empty());
        assert(the_list.front() == &b2);
        assert(the_list.back() == &b3);
        assert(the_list.is_head(&b2));
        assert(the_list.is_tail(&b3));
    }

    /// remove second element
    {
        assert(the_list.pop_front() == &b2);
        assert(not the_list.empty());
        assert(the_list.front() == &b3);
        assert(the_list.back() == &b3);
        assert(the_list.is_head(&b3));
        assert(the_list.is_tail(&b3));
    }

    /// remove last element
    {
        test_list_type::unlink(&b3);
        assert(the_list.empty());
    }

    /// movement
    {
        the_list.push_front(&b1);
        the_list.push_front(&b2);
        the_list.push_front(&b3);
        assert(the_list.front() == &b3);
        the_list.move_front(&b3);
        assert(the_list.front() == &b3);
        the_list.move_front(&b2);
        assert(the_list.front() == &b2);
        the_list.move_front(&b1);
        assert(the_list.front() == &b2);
        assert(the_list.back() == &b3);
        the_list.move_front(&b1);
        assert(the_list.pop_front() == &b1);
        assert(the_list.pop_front() == &b2);
        assert(the_list.pop_front() == &b3);
        assert(the_list.empty());
    }

    return 0 ;
}