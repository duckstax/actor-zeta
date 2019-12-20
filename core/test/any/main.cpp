#include <actor-zeta/detail/experimental_any.hpp>
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
    static int64_t  sTOCount;            // Count of all current existing TestObjects.
    static int64_t  sTOCtorCount;        // Count of times any ctor was called.
    static int64_t  sTODtorCount;        // Count of times dtor was called.
    static int64_t  sTODefaultCtorCount; // Count of times the default ctor was called.
    static int64_t  sTOArgCtorCount;     // Count of times the x0,x1,x2 ctor was called.
    static int64_t  sTOCopyCtorCount;    // Count of times copy ctor was called.
    static int64_t  sTOMoveCtorCount;    // Count of times move ctor was called.
    static int64_t  sTOCopyAssignCount;  // Count of times copy assignment was called.
    static int64_t  sTOMoveAssignCount;  // Count of times move assignment was called.
    static int      sMagicErrorCount;    // Number of magic number mismatch errors.

    explicit test_object(int x = 0, bool bThrowOnCopy = false)
            : mX(x), mbThrowOnCopy(bThrowOnCopy), mMagicValue(kMagicValue)
    {
        ++sTOCount;
        ++sTOCtorCount;
        ++sTODefaultCtorCount;
        mId = sTOCtorCount;
    }

    // This constructor exists for the purpose of testing variadiac template arguments, such as with the emplace container functions.
    test_object(int x0, int x1, int x2, bool bThrowOnCopy = false)
            : mX(x0 + x1 + x2), mbThrowOnCopy(bThrowOnCopy), mMagicValue(kMagicValue)
    {
        ++sTOCount;
        ++sTOCtorCount;
        ++sTOArgCtorCount;
        mId = sTOCtorCount;
    }

    test_object(const test_object& testObject)
            : mX(testObject.mX), mbThrowOnCopy(testObject.mbThrowOnCopy), mMagicValue(testObject.mMagicValue)
    {
        ++sTOCount;
        ++sTOCtorCount;
        ++sTOCopyCtorCount;
        mId = sTOCtorCount;
        if(mbThrowOnCopy)
        {
#if EASTL_EXCEPTIONS_ENABLED
            throw "Disallowed test_object copy";
#endif
        }
    }

    test_object(test_object&& testObject)
            : mX(testObject.mX), mbThrowOnCopy(testObject.mbThrowOnCopy), mMagicValue(testObject.mMagicValue)
    {
        ++sTOCount;
        ++sTOCtorCount;
        ++sTOMoveCtorCount;
        mId = sTOCtorCount;
        testObject.mX = 0;
        if(mbThrowOnCopy)
        {
#if EASTL_EXCEPTIONS_ENABLED
            throw "Disallowed test_object copy";
#endif
        }
    }

    test_object& operator=(const test_object& testObject){
        ++sTOCopyAssignCount;

        if(&testObject != this){
            mX = testObject.mX;
            // Leave mId alone.
            mMagicValue = testObject.mMagicValue;
            mbThrowOnCopy = testObject.mbThrowOnCopy;
            if(mbThrowOnCopy)
            {
#if EASTL_EXCEPTIONS_ENABLED
                throw "Disallowed test_object copy";
#endif
            }
        }
        return *this;
    }

    test_object& operator=(test_object&& testObject){
        ++sTOMoveAssignCount;

        if(&testObject != this){
            std::swap(mX, testObject.mX);
            // Leave mId alone.
            std::swap(mMagicValue, testObject.mMagicValue);
            std::swap(mbThrowOnCopy, testObject.mbThrowOnCopy);

            if(mbThrowOnCopy)
            {
#if EASTL_EXCEPTIONS_ENABLED
                throw "Disallowed test_object copy";
#endif
            }
        }
        return *this;
    }

    ~test_object(){
        if(mMagicValue != kMagicValue)
            ++sMagicErrorCount;
        mMagicValue = 0;
        --sTOCount;
        ++sTODtorCount;
    }

    static void Reset(){
        sTOCount            = 0;
        sTOCtorCount        = 0;
        sTODtorCount        = 0;
        sTODefaultCtorCount = 0;
        sTOArgCtorCount     = 0;
        sTOCopyCtorCount    = 0;
        sTOMoveCtorCount    = 0;
        sTOCopyAssignCount  = 0;
        sTOMoveAssignCount  = 0;
        sMagicErrorCount    = 0;
    }

    static bool IsClear() {
        return (sTOCount == 0) && (sTODtorCount == sTOCtorCount) && (sMagicErrorCount == 0);
    }
};

int64_t test_object::sTOCount            = 0;
int64_t test_object::sTOCtorCount        = 0;
int64_t test_object::sTODtorCount        = 0;
int64_t test_object::sTODefaultCtorCount = 0;
int64_t test_object::sTOArgCtorCount     = 0;
int64_t test_object::sTOCopyCtorCount    = 0;
int64_t test_object::sTOMoveCtorCount    = 0;
int64_t test_object::sTOCopyAssignCount  = 0;
int64_t test_object::sTOMoveAssignCount  = 0;
int     test_object::sMagicErrorCount    = 0;

struct small_test_object{
    static int mCtorCount;

    small_test_object() noexcept { mCtorCount++; }
    small_test_object(const small_test_object&) noexcept { mCtorCount++; }
    small_test_object(small_test_object&&) noexcept { mCtorCount++; }
    small_test_object& operator=(const small_test_object&) noexcept { mCtorCount++; return *this; }
    ~small_test_object() noexcept { mCtorCount--; }

    static void Reset() { mCtorCount = 0; }
    static bool IsClear() { return mCtorCount == 0; }
};

int small_test_object::mCtorCount = 0;


struct RequiresInitList{
    RequiresInitList(std::initializer_list<int> ilist): sum(std::accumulate(begin(ilist), end(ilist), 0)) {}

    int sum;
};


int main() {

    {
        static_assert(sizeof(std::string) <= sizeof(any), "ensure that 'any' has enough local memory to store a string");
        static_assert(sizeof(std::vector<int>) <= sizeof(any), "ensure that 'any' has enough local memory to store a vector");
    }

    {
        // default construct
        any a;
        assert(a.has_value() == false);
    }

    {
        // test object ctors & dtors are called for a large object
        test_object::Reset();
        { any a{test_object()}; }
        assert(test_object::IsClear());
    }

    {
        // test object ctors & dtors are called for a small object
        small_test_object::Reset();
        { any a{small_test_object()}; }
        assert(small_test_object::IsClear());
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
        struct custom_type { int data; };

        any a = custom_type{};
        any_cast<custom_type&>(a).data = 42;
        assert(any_cast<custom_type>(a).data == 42);
    }

    {
        any a = 42;
        assert(any_cast<int>(a) == 42);

#if EASTL_EXCEPTIONS_ENABLED
        int throwCount = 0;
			try { assert(any_cast<short>(a) == 42); }
			catch (bad_any_cast) { throwCount++;  }
			assert(throwCount != 0);
#endif
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
        test_object::Reset();
        {
            std::vector<any> va = {42, 'a', 42.f, 3333u, 4444ul, 5555ull, 6666.0};

            assert(any_cast<int>(va[0]) == 42);
            assert(any_cast<char>(va[1]) == 'a');
            assert(any_cast<float>(va[2]) == 42.f);
            assert(any_cast<unsigned>(va[3]) == 3333u);
            assert(any_cast<unsigned long>(va[4]) == 4444ul);
            assert(any_cast<unsigned long long>(va[5]) == 5555ull);
            assert(any_cast<double>(va[6]) == 6666.0);

            va[3] = test_object(3333); // replace a small integral with a large heap allocated object.

            assert(any_cast<int>(va[0]) == 42);
            assert(any_cast<char>(va[1]) == 'a');
            assert(any_cast<float>(va[2]) == 42.f);
            assert(any_cast<test_object>(va[3]).mX == 3333); // not 3333u because test_object ctor takes a signed type.
            assert(any_cast<unsigned long>(va[4]) == 4444ul);
            assert(any_cast<unsigned long long>(va[5]) == 5555ull);
            assert(any_cast<double>(va[6]) == 6666.0);
        }
        assert(test_object::IsClear());
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

    // swap tests
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

#if EASTL_RTTI_ENABLED
    {
		#if defined(EA_COMPILER_MSVC)
			assert(EA::StdC::Strcmp(any(42).type().name(), "int") == 0);
			assert(EA::StdC::Strcmp(any(42.f).type().name(), "float") == 0);
			assert(EA::StdC::Strcmp(any(42u).type().name(), "unsigned int") == 0);
			assert(EA::StdC::Strcmp(any(42ul).type().name(), "unsigned long") == 0);
			assert(EA::StdC::Strcmp(any(42l).type().name(), "long") == 0);

		#elif defined(EA_COMPILER_CLANG) || defined(EA_COMPILER_GNUC)
			assert(EA::StdC::Strcmp(any(42).type().name(), "i") == 0);
			assert(EA::StdC::Strcmp(any(42.f).type().name(), "f") == 0);
			assert(EA::StdC::Strcmp(any(42u).type().name(), "j") == 0);
			assert(EA::StdC::Strcmp(any(42ul).type().name(), "m") == 0);
			assert(EA::StdC::Strcmp(any(42l).type().name(), "l") == 0);
		#endif
	}
#endif

    // emplace, small object tests
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

    // emplace, large object tests
    {
        test_object::Reset();
        {
            any a;
            a.emplace<test_object>();
            assert(a.has_value());
        }
        assert(test_object::IsClear());
    }

    // emplace, initializer_list
    {
        {
            any a;
            a.emplace<RequiresInitList>(std::initializer_list<int>{1,2,3,4,5,6});

            assert(a.has_value());
            assert(any_cast<RequiresInitList>(a).sum == 21);
        }
    }

    // equivalence tests
    {
        any a, b;
        assert(!a.has_value() == !b.has_value());

#if EASTL_EXCEPTIONS_ENABLED
        int bad_any_cast_thrown = 0;
			try
			{
				assert(any_cast<int>(a) == any_cast<int>(b));
			}
			catch (eastl::bad_any_cast)
			{
				bad_any_cast_thrown++;
			}
			assert(bad_any_cast_thrown != 0);
#endif


        a = 42; b = 24;
        assert(any_cast<int>(a) != any_cast<int>(b));
        assert(a.has_value() == b.has_value());

        a = 42; b = 42;
        assert(any_cast<int>(a) == any_cast<int>(b));
        assert(a.has_value() == b.has_value());
    }

    // move tests
    {
        any a = std::string("hello world");
        assert(any_cast<std::string&>(a) == "hello world");

        auto s = move(any_cast<std::string&>(a)); // move string out
        assert(s == "hello world");
        assert(any_cast<std::string&>(a).empty());

        any_cast<std::string&>(a) = move(s); // move string in
        assert(any_cast<std::string&>(a) == "hello world");
    }

    // nullptr tests
    {
        any* a = nullptr;
        assert(any_cast<int>(a) == nullptr);
        assert(any_cast<short>(a) == nullptr);
        assert(any_cast<long>(a) == nullptr);
        assert(any_cast<std::string>(a) == nullptr);

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

    // make_any
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

    // user reported regression that eastl::any constructor was not decaying the deduced type correctly.
    {
        float f = 42.f;
        any a(f);
        assert(any_cast<float>(a) == 42.f);
    }

    //testing unsafe operations
    {
        any a = 1;
        int* i = any_cast<int>(&a);
        assert((*i) == 1);

        a = 2;
        int *j = (int*)unsafe_any_cast<void>(&a);
        assert((*j) == 2);

        const any b = 3;
        const void * p = unsafe_any_cast<void>(&b);
        void *q = const_cast<void *>(p);
        int *r = static_cast<int *>(q);
        assert((*r) == 3);
    }

    // user regression when calling the assignment operator
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