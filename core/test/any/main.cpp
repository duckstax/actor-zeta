#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include <actor-zeta/detail/any.hpp>
using actor_zeta::detail::any;
using actor_zeta::detail::any_cast;

class move_copy_conting_class {
public:
    static unsigned int moves_count;
    static unsigned int copy_count;

    move_copy_conting_class() = default;

    move_copy_conting_class(move_copy_conting_class && /*param*/) {
        ++moves_count;
    }

    move_copy_conting_class &operator=(move_copy_conting_class && /*param*/) {
        ++moves_count;
        return *this;
    }

    move_copy_conting_class(const move_copy_conting_class &) {
        ++copy_count;
    }

    move_copy_conting_class &operator=(const move_copy_conting_class & /*param*/) {
        ++copy_count;
        return *this;
    }
};

unsigned int move_copy_conting_class::moves_count = 0;
unsigned int move_copy_conting_class::copy_count = 0;

struct copy_counter {

public:

    copy_counter() = default;

    copy_counter(const copy_counter &) { ++count; }

    copy_counter &operator=(const copy_counter &) {
        ++count;
        return *this;
    }

    static int get_count() { return count; }

private:

    static int count;

};

int copy_counter::count = 0;

template<typename T>
class class_with_address_op {
public:
    explicit class_with_address_op(const T *p): ptr(p) {}

    const T **operator&() {
        return &ptr;
    }

    const T *get() const {
        return ptr;
    }

private:
    const T *ptr;
};

void test_default_ctor() {
    const any value;

    assert(!value.has_value());//  "no empty");
    auto*d  = any_cast<int>(&value);
    assert(d == nullptr);//  "any_cast<int>");
}

void test_converting_ctor() {
    std::string text = "test message";
    any value = text;

    assert(value.has_value());//  "empty");
    assert(any_cast<int>(&value ) == nullptr);//  "any_cast<int>");
    assert(any_cast<std::string>(&value) != nullptr);//  "any_cast<std::string>");
    assert(any_cast<std::string>(value) == text);// "comparing cast copy against original text");
    assert(any_cast<std::string>(&value)!= &text);// "comparing address in copy against original text");
}

void test_copy_ctor() {
    std::string text = "test message";
    any original = text, copy = original;

    assert(copy.has_value());//  "empty");
    assert(any_cast<std::string>(original) == any_cast<std::string>(copy));// "comparing cast copy against original");
    assert(text == any_cast<std::string>(copy));// "comparing cast copy against original text");
    assert(any_cast<std::string>(&original)!= any_cast<std::string>(&copy));// "comparing address in copy against original");
}

void test_copy_assign() {
    std::string text = "test message";
    any original = text, copy;
    any *assign_result = &(copy = original);

    assert(copy.has_value());//  "empty");
    assert(any_cast<std::string>(original) == any_cast<std::string>(copy));// "comparing cast copy against cast original");
    assert(text == any_cast<std::string>(copy));// "comparing cast copy against original text");
    assert(any_cast<std::string>(&original) != any_cast<std::string>(&copy));// "comparing address in copy against original");
    assert(assign_result == &copy);// "address of assignment result");
}

void test_converting_assign() {
    std::string text = "test message";
    any value;
    any *assign_result = &(value = text);

    assert(value.has_value());//  "empty");
    assert(any_cast<int>(&value)==nullptr);//  "any_cast<int>");
    assert(any_cast<std::string>(&value)!=nullptr);//  "any_cast<std::string>");
    assert(any_cast<std::string>(value) == text);// "comparing cast copy against original text");
    assert(any_cast<std::string>(&value)!=&text);// "comparing address in copy against original text");
    assert(assign_result == &value);//  "address of assignment result");
}
/*

void test_swap() {
    std::string text = "test message";
    any original = text swapped;
    std::string *original_ptr = any_cast<std::string>(&original);
    any *swap_result = &original.swap(swapped);

    assert(original.has_value());//empty
    assert(swapped.has_value());//empty
    assert(text == any_cast<std::string>(swapped));// "comparing swapped copy against original text
    assert(original_ptr!= nullptr);//address in pre-swapped original
    assert(original_ptr == any_cast<std::string>(&swapped));// "comparing address in swapped against original
    assert(swap_result == &original);//address of swap result

    any copy1 = copy_counter();
    any copy2 = copy_counter();
    int count = copy_counter::get_count();
    swap(copy1, copy2);
    assert(count == copy_counter::get_count());//checking that free swap doesn't make any copies.
}
*/
void test_null_copying() {
    const any null;
    any copied = null, assigned;
    assigned = null;

    assert(null.has_value());//empty on null
    assert(copied.has_value());//empty on copied
    assert(assigned.has_value());//empty on copied");
}
/*
void test_cast_to_reference() {
    any a(137);
    const any b(a);

    int &ra = any_cast<int &>(a);
    int const &ra_c = any_cast < int const & > (a);
    int volatile &ra_v = any_cast < int volatile & > (a);
    int const volatile &ra_cv = any_cast < int const volatile& > (a);

    assert(&ra == &ra_c && &ra == &ra_v && &ra == &ra_cv);///cv references to same obj

    int const &rb_c = any_cast < int const & > (b);
    int const volatile &rb_cv = any_cast < int const volatile & > (b);

    assert(&rb_c == &rb_cv);//cv references to copied const obj
    assert((&ra != &rb_c);///copies hold different objects

    ++ra;
    int incremented = any_cast<int>(a);
    assert(incremented == 138);///increment by reference changes value
}
*/
void test_with_array() {
    any value1("Char array");
    any value2;
    value2 = "Char array";

    assert(value1.has_value());//type
    assert(value2.has_value());//type

    assert(any_cast<const char *>(&value1)!= nullptr);//any_cast<const char*>
    assert(any_cast<const char *>(&value2)!= nullptr);//any_cast<const char*>
}

void test_clear() {
    std::string text = "test message";
    any value = text;
    assert(value.has_value());//empty
    value.reset();
    assert(value.has_value());//non-empty after clear
    value.reset();
    assert(value.has_value());//non-empty after second clear
    value = text;
    assert(value.has_value());//empty
    value.reset();
    assert(value.has_value());//non-empty after clear
}


any makeVec() {
    return std::vector<int>(100 /*size*/, 7 /*value*/);
}

void test_vectors() {
    const std::vector<int> &vec = any_cast<std::vector<int> >(makeVec());
    assert(vec.size() == 100u);//size of vector extracted from boost::any
    assert(vec.back()== 7);//back value of vector extracted from boost::any
    assert(vec.front() == 7);//front value of vector extracted from boost::any

    std::vector<int> vec1 = any_cast<std::vector<int> >(makeVec());
    assert(vec1.size() == 100u);//size of second vector extracted from boost::any
    assert(vec1.back()== 7);//back value of second vector extracted from boost::any
    assert(vec1.front()== 7);//front value of second vector extracted from boost::any

}
/*
void test_addressof() {
    int val = 10;
    const int *ptr = &val;
    class_with_address_op<int> obj(ptr);
    any test_val(obj);

    class_with_address_op<int> returned_obj = any_cast<class_with_address_op<int> >(test_val);
    assert(&val == returned_obj.get());///any_cast incorrectly works with type that has operator&(): addresses differ
    assert(!!any_cast<class_with_address_op<int> >(&test_val));///any_cast incorrectly works with type that has operator&()
    assert(unsafe_any_cast<class_with_address_op<int> >(&test_val)->get() == ptr);//unsafe_any_cast incorrectly works with type that has operator&()
}
*/
void test_move_construction() {
    any value0 = move_copy_conting_class();
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;
    any value(std::move(value0));

    assert(value0.has_value());//moved away is empty
    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value) != nullptr);// "any_cast<move_copy_conting_class>
    assert(move_copy_conting_class::copy_count == 0u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts
}

void test_move_assignment() {
    any value0 = move_copy_conting_class();
    any value = move_copy_conting_class();
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;
    value = std::move(value0);

    assert(value0.has_value());//moved away is empty
    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value)!= nullptr);//any_cast<move_copy_conting_class>
    assert(move_copy_conting_class::copy_count == 0u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts
}

void test_copy_construction() {
    any value0 = move_copy_conting_class();
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;
    any value(value0);

    assert(value0.has_value());//moved away is empty
    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value)!= nullptr);//any_cast<move_copy_conting_class>
    assert(move_copy_conting_class::copy_count == 1u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts
}

void test_copy_assignment() {
    any value0 = move_copy_conting_class();
    any value = move_copy_conting_class();
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;
    value = value0;

    assert(value0.has_value());//moved away is empty
    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value)!= nullptr);//any_cast<move_copy_conting_class>
    assert(move_copy_conting_class::copy_count== 1u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts
}

void test_move_construction_from_value() {
    move_copy_conting_class value0;
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;
    any value(std::move(value0));

    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value)!=nullptr);//any_cast<move_copy_conting_class>

    assert(move_copy_conting_class::copy_count== 1u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts
}

void test_move_assignment_from_value() {
    move_copy_conting_class value0;
    any value;
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;

    value = std::move(value0);

    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value)!=nullptr);//any_cast<move_copy_conting_class>
    assert(move_copy_conting_class::copy_count == 1u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts


}

void test_copy_construction_from_value() {
    move_copy_conting_class value0;
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;
    any value(value0);

    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value)!= nullptr);//any_cast<move_copy_conting_class>
    assert(move_copy_conting_class::copy_count == 1u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts
}

void test_copy_assignment_from_value() {
    move_copy_conting_class value0;
    any value;
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;
    value = value0;

    assert(value.has_value());//empty
    assert(any_cast<move_copy_conting_class>(&value)!= nullptr);//any_cast<move_copy_conting_class>
    assert(move_copy_conting_class::copy_count == 1u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 0u);//checking move counts
}

const any helper_method() {
    return true;
}

bool helper_method1() {
    return true;
}

void test_construction_from_const_any_rv() {
    any values[] = {helper_method(), helper_method1()};
    (void) values;
}
/*
void test_cast_to_rv() {
    move_copy_conting_class value0;
    any value;
    value = value0;
    move_copy_conting_class::copy_count = 0;
    move_copy_conting_class::moves_count = 0;

    move_copy_conting_class value1 = any_cast<move_copy_conting_class &&>(value);

    assert(move_copy_conting_class::copy_count== 0u);//checking copy counts
    assert(move_copy_conting_class::moves_count == 1u);// "checking move counts
    (void) value1;
}
*/

int main() {

    test_default_ctor();
    test_converting_ctor();
    test_copy_ctor();
    test_copy_assign();
    test_converting_assign();
    //test_bad_cast();
//    test_swap();
    test_null_copying();
    //test_cast_to_reference();
    test_with_array();
    test_clear();
    test_vectors();
    //test_addressof();
    test_move_construction();
    test_move_assignment();
    test_copy_construction();
    test_copy_assignment();
    test_move_construction_from_value();
    test_move_assignment_from_value();
    test_copy_construction_from_value();
    test_copy_assignment_from_value();
    test_construction_from_const_any_rv();
    //test_cast_to_rv();

    return 0;
}