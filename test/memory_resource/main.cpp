#include <actor-zeta/detail/pmr/memory_resource.hpp>

#include <cassert>

using actor_zeta::detail::pmr::memory_resource;

class derived_from_memory_resource
    : public memory_resource {
public:
    explicit derived_from_memory_resource(unsigned i = 0u)
        : id(i) {}

    virtual ~derived_from_memory_resource() { destructor_called = true; }

    virtual void* do_allocate(std::size_t bytes, std::size_t alignment) {
        do_allocate_called = true;
        do_allocate_bytes = bytes;
        do_allocate_alignment = alignment;
        return do_allocate_return;
    }

    virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
        do_deallocate_called = true;
        do_deallocate_p = p;
        do_deallocate_bytes = bytes;
        do_deallocate_alignment = alignment;
    }

    virtual bool do_is_equal(const memory_resource& other) const noexcept {
        do_is_equal_called = true;
        do_is_equal_other = &other;
        return static_cast<const derived_from_memory_resource&>(other).id == this->id;
    }

    void reset() {
        destructor_called = false;

        do_allocate_return = 0;
        do_allocate_called = false;
        do_allocate_bytes = 0u;
        do_allocate_alignment = 0u;

        do_deallocate_called = false;
        do_deallocate_p = 0;
        do_deallocate_bytes = 0u;
        do_deallocate_alignment = 0u;

        do_is_equal_called = false;
        do_is_equal_other = 0;
    }

    static bool destructor_called;

    unsigned id;
    void* do_allocate_return;
    mutable bool do_allocate_called;
    mutable std::size_t do_allocate_bytes;
    mutable std::size_t do_allocate_alignment;

    mutable bool do_deallocate_called;
    mutable void* do_deallocate_p;
    mutable std::size_t do_deallocate_bytes;
    mutable std::size_t do_deallocate_alignment;

    mutable bool do_is_equal_called;
    mutable const memory_resource* do_is_equal_other;
};

bool derived_from_memory_resource::destructor_called = false;

void test_allocate() {
    derived_from_memory_resource d;
    memory_resource& mr = d;

    d.reset();
    assert(d.do_allocate_called == false);
    assert(d.do_allocate_bytes == 0);
    assert(d.do_allocate_alignment == 0);

    mr.allocate(2, 4);
    assert(d.do_allocate_called == true);
    assert(d.do_allocate_bytes == 2);
    assert(d.do_allocate_alignment == 4);
}

void test_deallocate() {
    derived_from_memory_resource d;
    memory_resource& mr = d;

    d.reset();
    assert(d.do_deallocate_called == false);
    assert(d.do_deallocate_p == 0);
    assert(d.do_allocate_bytes == 0);
    assert(d.do_allocate_alignment == 0);

    mr.deallocate(&d, 2, 4);
    assert(d.do_deallocate_called == true);
    assert(d.do_deallocate_p == &d);
    assert(d.do_deallocate_bytes == 2);
    assert(d.do_deallocate_alignment == 4);
}

void test_destructor() {
    {
        derived_from_memory_resource d;
        d.reset();
        assert(derived_from_memory_resource::destructor_called == false);
    }
    assert(derived_from_memory_resource::destructor_called == true);
}

void test_is_equal() {
    derived_from_memory_resource d;
    memory_resource& mr = d;

    d.reset();
    assert(d.do_is_equal_called == false);
    assert(d.do_is_equal_other == 0);

    mr.is_equal(d);
    assert(d.do_is_equal_called == true);
    assert(d.do_is_equal_other == &d);
}

void test_equality_operator() {
    derived_from_memory_resource d;
    memory_resource& mr = d;

    d.reset();
    assert(d.do_is_equal_called == false);
    assert(d.do_is_equal_other == 0);

    assert((mr == mr) == true);
    assert(d.do_is_equal_called == false);
    assert(d.do_is_equal_other == 0);

    derived_from_memory_resource d2(1);
    d.reset();
    d2.reset();
    memory_resource& mr2 = d2;
    assert((mr == mr2) == false);
    assert(d.do_is_equal_called == true);
    assert(d.do_is_equal_other == &d2);
}

void test_inequality_operator() {
    derived_from_memory_resource d;
    memory_resource& mr = d;

    d.reset();
    assert(d.do_is_equal_called == false);
    assert(d.do_is_equal_other == 0);

    assert((mr != mr) == false);
    assert(d.do_is_equal_called == false);
    assert(d.do_is_equal_other == 0);

    derived_from_memory_resource d2(1);
    d.reset();
    d2.reset();
    memory_resource& mr2 = d2;
    assert((mr != mr2) == true);
    assert(d.do_is_equal_called == true);
    assert(d.do_is_equal_other == &d2);
}

int main() {
    test_destructor();
    test_allocate();
    test_deallocate();
    test_is_equal();
    test_equality_operator();
    test_inequality_operator();
    return 0;
}