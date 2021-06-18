#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>
#include <actor-zeta/detail/type_traits.hpp>

#include <cassert>

using actor_zeta::detail::pmr::memory_resource;
using actor_zeta::detail::pmr::polymorphic_allocator;

struct x {
    x() =default;
    x(int value):value_(value){}
    int value_ = 0;
};

using test_type = polymorphic_allocator<x>;

static_assert(std::is_destructible<test_type>{}, "");
static_assert(std::is_copy_constructible<test_type>{}, "");
static_assert(std::is_copy_assignable<test_type>{}, "");
static_assert(std::is_constructible<test_type, memory_resource*>{}, "");
static_assert(std::is_same<test_type::value_type, x>{}, "");
static_assert(!std::is_polymorphic<test_type>{}, "");
static_assert(!std::is_final<test_type>{}, "");

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

void test_resource_constructor() {
    derived_from_memory_resource d;
    polymorphic_allocator<int> b(&d);
    assert(&d == b.resource());
}

void test_copy_constructor() {
    derived_from_memory_resource d;
    polymorphic_allocator<int> b(&d);
    polymorphic_allocator<int> c(b);
    assert(b.resource() == c.resource());
}

void test_copy_assignment() {
    derived_from_memory_resource d;
    polymorphic_allocator<int> b(&d);
    auto c = b;
    assert(c.resource() == b.resource());
}

void test_allocate() {
    int dummy;
    derived_from_memory_resource d;
    polymorphic_allocator<int> p(&d);
    d.reset();
    d.do_allocate_return = &dummy;
    p.allocate(2);
    assert(d.do_allocate_called == true);
    assert(d.do_allocate_return == &dummy);
    //It shall allocate 2*sizeof(int), alignment_of<int>
    assert(d.do_allocate_bytes == 2 * sizeof(int));
    assert(d.do_allocate_alignment == std::alignment_of<int>::value);
}

void test_deallocate() {
    int dummy;
    derived_from_memory_resource d;
    polymorphic_allocator<int> p(&d);
    d.reset();
    p.deallocate(&dummy, 3);
    assert(d.do_deallocate_called == true);
    //It shall deallocate 2*sizeof(int), alignment_of<int>
    assert(d.do_deallocate_p == &dummy);
    assert(d.do_deallocate_bytes == 3 * sizeof(int));
    assert(d.do_deallocate_alignment == std::alignment_of<int>::value);
}

void test_construct() {
    {
        using value_type = x;
        value_type value;
        value.~value_type();
        derived_from_memory_resource d;
        polymorphic_allocator<int> pa(&d);
        pa.construct(&value);
        assert(value.value_ == 0);
        value.~value_type();
    }

    {
        using value_type = x;
        value_type value;
        value.~value_type();
        derived_from_memory_resource d;
        polymorphic_allocator<int> pa(&d);
        pa.construct(&value, 2);
        assert(value.value_ == 2);
        value.~value_type();
    }

}

struct char_holder {
    char m_char;
    ~char_holder() { destructor_called = true; }
    static bool destructor_called;
};

bool char_holder::destructor_called = false;

void test_destroy() {
    char_holder ch;
    derived_from_memory_resource d;
    polymorphic_allocator<int> p(&d);
    assert(char_holder::destructor_called == false);
    p.destroy(&ch);
    assert(char_holder::destructor_called == true);
}

void test_resource() {
    derived_from_memory_resource d;
    polymorphic_allocator<int> p(&d);
    assert(&d == p.resource());
}

int main() {
    test_resource_constructor();
    test_copy_constructor();
    test_copy_assignment();
    test_allocate();
    test_deallocate();
    test_construct();
    test_destroy();
    test_resource();
    return 0;
}