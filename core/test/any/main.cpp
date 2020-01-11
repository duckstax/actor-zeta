#include <actor-zeta/detail/any.hpp>
#include <numeric>
#include <vector>
#include <string>
#include <cassert>

using actor_zeta::detail::any;
using actor_zeta::detail::any_cast;
using actor_zeta::detail::make_any;
using actor_zeta::detail::unsafe_any_cast;

const uint32_t kMagicValue = 0x01f1cbe8;

struct test_object final {
    int             mX;                  // Value for the test_object.
    bool            mbThrowOnCopy;       // Throw an exception of this object is copied, moved, or assigned to another.
    int64_t         mId;                 // Unique id for each object, equal to its creation number. This value is not coped from other TestObjects during any operations, including moves.
    uint32_t        mMagicValue;         // Used to verify that an instance is valid and that it is not corrupted. It should always be kMagicValue.
    static int64_t  count;            // Count of all current existing TestObjects.
    static int64_t  ctor_count;        // Count of times any ctor was called.
    static int64_t  dtor_count;        // Count of times dtor was called.
    static int64_t  default_ctor_count; // Count of times the default ctor was called.
    static int64_t  arg_ctor_count;     // Count of times the x0,x1,x2 ctor was called.
    static int64_t  copy_ctor_count;    // Count of times copy ctor was called.
    static int64_t  move_ctor_count;    // Count of times move ctor was called.
    static int64_t  copy_assign_count;  // Count of times copy assignment was called.
    static int64_t  move_assign_count;  // Count of times move assignment was called.
    static int      sMagicErrorCount;    // Number of magic number mismatch errors.

    explicit test_object(int x = 0, bool bThrowOnCopy = false)
            : mX(x), mbThrowOnCopy(bThrowOnCopy), mMagicValue(kMagicValue)
    {
        ++count;
        ++ctor_count;
        ++default_ctor_count;
        mId = ctor_count;
    }

    test_object(int x0, int x1, int x2, bool bThrowOnCopy = false)
            : mX(x0 + x1 + x2), mbThrowOnCopy(bThrowOnCopy), mMagicValue(kMagicValue)
    {
        ++count;
        ++ctor_count;
        ++arg_ctor_count;
        mId = ctor_count;
    }

    test_object(const test_object& testObject)
            : mX(testObject.mX), mbThrowOnCopy(testObject.mbThrowOnCopy), mMagicValue(testObject.mMagicValue)
    {
        ++count;
        ++ctor_count;
        ++copy_ctor_count;
        mId = ctor_count;
    }

    test_object(test_object&& testObject)
            : mX(testObject.mX), mbThrowOnCopy(testObject.mbThrowOnCopy), mMagicValue(testObject.mMagicValue)
    {
        ++count;
        ++ctor_count;
        ++move_ctor_count;
        mId = ctor_count;
        testObject.mX = 0;
    }

    test_object& operator=(const test_object& testObject){
        ++copy_assign_count;

        if(&testObject != this){
            mX = testObject.mX;
            mMagicValue = testObject.mMagicValue;
            mbThrowOnCopy = testObject.mbThrowOnCopy;
        }
        return *this;
    }

    test_object& operator=(test_object&& testObject){
        ++move_assign_count;

        if(&testObject != this){
            std::swap(mX, testObject.mX);
            std::swap(mMagicValue, testObject.mMagicValue);
            std::swap(mbThrowOnCopy, testObject.mbThrowOnCopy);
        }
        return *this;
    }

    ~test_object(){
        if(mMagicValue != kMagicValue) {
            ++sMagicErrorCount;
        }
        mMagicValue = 0;
        --count;
        ++dtor_count;
    }

    static void reset(){
        count            = 0;
        ctor_count        = 0;
        dtor_count        = 0;
        default_ctor_count = 0;
        arg_ctor_count     = 0;
        copy_ctor_count    = 0;
        move_ctor_count    = 0;
        copy_assign_count  = 0;
        move_assign_count  = 0;
        sMagicErrorCount    = 0;
    }

    static bool is_clear() {
        return (count == 0) && (dtor_count == ctor_count) && (sMagicErrorCount == 0);
    }
};

int64_t test_object::count              = 0;
int64_t test_object::ctor_count         = 0;
int64_t test_object::dtor_count         = 0;
int64_t test_object::default_ctor_count = 0;
int64_t test_object::arg_ctor_count     = 0;
int64_t test_object::copy_ctor_count    = 0;
int64_t test_object::move_ctor_count    = 0;
int64_t test_object::copy_assign_count  = 0;
int64_t test_object::move_assign_count  = 0;
int     test_object::sMagicErrorCount   = 0;

struct small_test_object final {
    static int mCtorCount;

    small_test_object() noexcept { mCtorCount++; }
    small_test_object(const small_test_object&) noexcept { mCtorCount++; }
    small_test_object(small_test_object&&) noexcept { mCtorCount++; }
    small_test_object& operator=(const small_test_object&) noexcept { mCtorCount++; return *this; }
    ~small_test_object() noexcept { mCtorCount--; }

    static void reset() { mCtorCount = 0; }
    static bool is_clear() { return mCtorCount == 0; }
};

int small_test_object::mCtorCount = 0;


struct RequiresInitList final {
    RequiresInitList(std::initializer_list<int> ilist): sum(std::accumulate(begin(ilist), end(ilist), 0)) {}

    int sum;
};

template <typename... Ts>
void ignore_unused(Ts const& ...){}

template <typename... Ts>
void ignore_unused(){}


int main() {

    {
        static_assert(sizeof(std::string) <= sizeof(any), "ensure that 'any' has enough local memory to store a string");
        static_assert(sizeof(std::vector<int>) <= sizeof(any), "ensure that 'any' has enough local memory to store a vector");
    }

    {
        any a;
        assert(!a.has_value());
    }

    {
        test_object::reset();
        { any a{test_object()}; }
        assert(!test_object::is_clear());
    }

    {
        small_test_object::reset();
        { any a{small_test_object()}; }
        assert(small_test_object::is_clear());
    }

    {
        any a(42);
        assert(a.has_value() == true);

        assert(any_cast<int>(a) == 42);
        assert(any_cast<int>(a) != 1337);
        any_cast<int&>(a) = 10;
        assert(any_cast<int>(a) == 10);

        a = 1.f;
        any_cast<float&>(a) = 1337.f;
        assert(any_cast<float>(a) == 1337.f);

        a = 4343;
        assert(any_cast<int>(a) == 4343);

        a = std::string("hello world");
        assert(any_cast<std::string>(a) == "hello world");
        assert(any_cast<std::string&>(a) == "hello world");
    }

    {
        struct custom_type {
            custom_type():data_(){}
            int data_;
        };

        any a = custom_type();
        any_cast<custom_type&>(a).data_ = 42;
        assert(any_cast<custom_type>(a).data_ == 42);
    }

    {
        any a = 42;
        assert(any_cast<int>(a) == 42);
    }

    {
        std::vector<any> va = {42, 'a', 42.f, 3333u, 4444ul, 5555ull, 6666.0};

        assert(any_cast<int>(va[0]) == 42);
        assert(any_cast<char>(va[1]) == 'a');
        assert(any_cast<float>(va[2]) == 42.f);
        assert(any_cast<unsigned>(va[3]) == 3333u);
        assert(any_cast<unsigned long>(va[4]) == 4444ul);
        assert(any_cast<unsigned long long>(va[5]) == 5555ull);
        assert(any_cast<double>(va[6]) == 6666.0);
    }

    {
        any a(std::string("test string"));
        assert(a.has_value());
        assert(any_cast<std::string>(a) == "test string");
    }

    {
        std::vector<any> va = {42, std::string("rob"), 'a', 42.f};
        assert(any_cast<int>(va[0]) == 42);
        assert(any_cast<std::string>(va[1]) == "rob");
        assert(any_cast<char>(va[2]) == 'a');
        assert(any_cast<float>(va[3]) == 42.f);
    }

    {
        std::vector<any> va;
        va.push_back(42);
        va.push_back(std::string("rob"));
        va.push_back('a');
        va.push_back(42.f);

        assert(any_cast<int>(va[0]) == 42);
        assert(any_cast<std::string>(va[1]) == "rob");
        assert(any_cast<char>(va[2]) == 'a');
        assert(any_cast<float>(va[3]) == 42.f);
    }

    {
        test_object::reset();
        {
            std::vector<any> va = {42, 'a', 42.f, 3333u, 4444ul, 5555ull, 6666.0};

            assert(any_cast<int>(va[0]) == 42);
            assert(any_cast<char>(va[1]) == 'a');
            assert(any_cast<float>(va[2]) == 42.f);
            assert(any_cast<unsigned>(va[3]) == 3333u);
            assert(any_cast<unsigned long>(va[4]) == 4444ul);
            assert(any_cast<unsigned long long>(va[5]) == 5555ull);
            assert(any_cast<double>(va[6]) == 6666.0);

            va[3] = test_object(3333);

            assert(any_cast<int>(va[0]) == 42);
            assert(any_cast<char>(va[1]) == 'a');
            assert(any_cast<float>(va[2]) == 42.f);
            assert(any_cast<test_object>(va[3]).mX == 3333);
            assert(any_cast<unsigned long>(va[4]) == 4444ul);
            assert(any_cast<unsigned long long>(va[5]) == 5555ull);
            assert(any_cast<double>(va[6]) == 6666.0);
        }
        assert(!test_object::is_clear());
    }

    {
        any a(std::string("test string"));
        assert(a.has_value());
        a.reset();
        assert(!a.has_value());
    }

    {
        any a1 = 42;
        any a2 = a1;

        assert(a1.has_value());
        assert(a2.has_value());
        assert(any_cast<int>(a1) == any_cast<int>(a2));
    }

    {
        any a1;
        assert(!a1.has_value());
        {
            any a2(std::string("test string"));
            a1 = any_cast<std::string>(a2);

            assert(a1.has_value());
        }
        assert(any_cast<std::string>(a1) == "test string");
        assert(a1.has_value());
    }

    {
        any a1;
        assert(!a1.has_value());
        {
            any a2(std::string("test string"));
            a1 = a2;
            assert(a1.has_value());
        }
        assert(any_cast<std::string&>(a1) == "test string");
        assert(a1.has_value());
    }

    {
        {
            any a1 = 42;
            any a2 = 24;
            assert(any_cast<int>(a1) == 42);
            assert(any_cast<int>(a2) == 24);

            a1.swap(a2);
            assert(any_cast<int>(a1) == 24);
            assert(any_cast<int>(a2) == 42);

            std::swap(a1, a2);
            assert(any_cast<int>(a1) == 42);
            assert(any_cast<int>(a2) == 24);
        }
        {
            any a1 = std::string("hello");
            any a2 = std::string("world");
            assert(any_cast<std::string>(a1) == "hello");
            assert(any_cast<std::string>(a2) == "world");

            a1.swap(a2);
            assert(any_cast<std::string>(a1) == "world");
            assert(any_cast<std::string>(a2) == "hello");

            std::swap(a1, a2);
            assert(any_cast<std::string>(a1) == "hello");
            assert(any_cast<std::string>(a2) == "world");
        }
    }

    {
        any a;

        a.emplace<int>(42);
        assert(a.has_value());
        assert(any_cast<int>(a) == 42);

        a.emplace<short>((short)8); // no way to define a short literal we must cast here.
        assert(any_cast<short>(a) == 8);
        assert(a.has_value());

        a.reset();
        assert(!a.has_value());
    }

    {
        test_object::reset();
        {
            any a;
            a.emplace<test_object>();
            assert(a.has_value());
        }
        assert(!test_object::is_clear());
    }

    {
        {
            any a;
            a.emplace<RequiresInitList>(std::initializer_list<int>{1,2,3,4,5,6});

            assert(a.has_value());
            assert(any_cast<RequiresInitList>(a).sum == 21);
        }
    }

    {
        any a, b;
        assert(!a.has_value() == !b.has_value());

        a = 42; b = 24;
        assert(any_cast<int>(a) != any_cast<int>(b));
        assert(a.has_value() == b.has_value());

        a = 42; b = 42;
        assert(any_cast<int>(a) == any_cast<int>(b));
        assert(a.has_value() == b.has_value());
    }

    {
        any a = std::string("hello world");
        assert(any_cast<std::string&>(a) == "hello world");

        auto s = move(any_cast<std::string&>(a));
        assert(s == "hello world");
        assert(any_cast<std::string&>(a).empty());

        any_cast<std::string&>(a) = move(s);
        assert(any_cast<std::string&>(a) == "hello world");
    }

    {
        any* a = nullptr;
        assert(any_cast<int>(a) == nullptr);
        assert(any_cast<short>(a) == nullptr);
        assert(any_cast<long>(a) == nullptr);
        assert(any_cast<std::string>(a) == nullptr);
        ignore_unused(a);

        any b;
        assert(any_cast<short>(&b) == nullptr);
        assert(any_cast<const short>(&b) == nullptr);
        assert(any_cast<volatile short>(&b) == nullptr);
        assert(any_cast<const volatile short>(&b) == nullptr);

        assert(any_cast<short*>(&b) == nullptr);
        assert(any_cast<const short*>(&b) == nullptr);
        assert(any_cast<volatile short*>(&b) == nullptr);
        assert(any_cast<const volatile short*>(&b) == nullptr);
    }

    {
        {
            auto a = make_any<int>(42);
            assert(any_cast<int>(a) == 42);
        }

        {
            auto a = make_any<RequiresInitList>(std::initializer_list<int>{1,2,3,4,5,6,7,8});
            assert(any_cast<RequiresInitList&>(a).sum == 36);
        }
    }

    {
        float f = 42.f;
        any a(f);
        assert(any_cast<float>(a) == 42.f);
    }

    {
        any a = 1;
        int* i = any_cast<int>(&a);
        assert((*i) == 1);
        ignore_unused(i);

        a = 2;
        int *j = (int*)unsafe_any_cast<void>(&a);
        assert((*j) == 2);
        ignore_unused(j);

        const any b = 3;
        const void * p = unsafe_any_cast<void>(&b);
        void *q = const_cast<void *>(p);
        int *r = static_cast<int *>(q);
        assert((*r) == 3);
        ignore_unused(r);
    }

    {
        {
            any a1;
            any a2;
            assert(a1.has_value() == false);
            assert(a2.has_value() == false);

            a1 = a2;
            assert(a1.has_value() == false);
            assert(a2.has_value() == false);
        }

        {
            any a1 = 42;
            any a2;
            assert(a1.has_value() == true);
            assert(a2.has_value() == false);

            a1 = a2;
            assert(a1.has_value() == false);
            assert(a2.has_value() == false);
        }

        {
            any a1;
            any a2 = 42;
            assert(a1.has_value() == false);
            assert(a2.has_value() == true);

            a1 = a2;
            assert(a1.has_value() == true);
            assert(a2.has_value() == true);
            assert(any_cast<int>(a1) == 42);
            assert(any_cast<int>(a2) == 42);
        }
    }

    return 0;
}