
#include <cassert>
#include <actor-zeta/messaging/message.hpp>



int main() {
    actor_zeta::messaging::message b1, b2, b3;

    using message_list_type = actor_zeta::intrusive_list<actor_zeta::messaging::message, &actor_zeta::messaging::message::link>;

    message_list_type the_list;
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
        message_list_type::unlink(&b1);
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
        message_list_type::unlink(&b3);
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