#include <actor-zeta/detail/any.hpp>
#include <numeric>
#include <vector>
#include <string>
#include <cassert>

using actor_zeta::detail::any;
using actor_zeta::detail::any_cast;
using actor_zeta::detail::make_any;
using actor_zeta::detail::unsafe_any_cast;

const uint32_t magic_value = 0x01f1cbe8;

struct big_object final {
    int             x_;
    bool            throw_on_copy_;
    int64_t         id_;
    uint32_t        magic_value_;
    static int64_t  counter_;
    static int64_t  constructor_counter_;
    static int64_t  dtor_counter_;
    static int64_t  default_constructor_counter_;
    static int64_t  arg_constructor_counter_;
    static int64_t  copy_constructor_counter_;
    static int64_t  move_constructor_counter_;
    static int64_t  copy_assign_counter_;
    static int64_t  move_assign_counter_;
    static int      magic_error_counter_;

    explicit big_object(int x = 0, bool bThrowOnCopy = false)
            : x_(x), throw_on_copy_(bThrowOnCopy), magic_value_(magic_value)
    {
        ++counter_;
        ++constructor_counter_;
        ++default_constructor_counter_;
        id_ = constructor_counter_;
    }

    big_object(int x0, int x1, int x2, bool bThrowOnCopy = false)
            : x_(x0 + x1 + x2), throw_on_copy_(bThrowOnCopy), magic_value_(magic_value)
    {
        ++counter_;
        ++constructor_counter_;
        ++arg_constructor_counter_;
        id_ = constructor_counter_;
    }

    big_object(const big_object& testObject)
            : x_(testObject.x_), throw_on_copy_(testObject.throw_on_copy_), magic_value_(testObject.magic_value_)
    {
        ++counter_;
        ++constructor_counter_;
        ++copy_constructor_counter_;
        id_ = constructor_counter_;
    }

    big_object(big_object&& testObject)
            : x_(testObject.x_), throw_on_copy_(testObject.throw_on_copy_), magic_value_(testObject.magic_value_)
    {
        ++counter_;
        ++constructor_counter_;
        ++move_constructor_counter_;
        id_ = constructor_counter_;
        testObject.x_ = 0;
    }

    big_object& operator=(const big_object& testObject){
        ++copy_assign_counter_;

        if(&testObject != this){
            x_ = testObject.x_;
            magic_value_ = testObject.magic_value_;
            throw_on_copy_ = testObject.throw_on_copy_;
        }
        return *this;
    }

    big_object& operator=(big_object&& testObject){
        ++move_assign_counter_;

        if(&testObject != this){
            std::swap(x_, testObject.x_);
            std::swap(magic_value_, testObject.magic_value_);
            std::swap(throw_on_copy_, testObject.throw_on_copy_);
        }
        return *this;
    }

    ~big_object(){
        if(magic_value_ != magic_value) {
            ++magic_error_counter_;
        }
        magic_value_ = 0;
        --counter_;
        ++dtor_counter_;
    }

    static void reset(){
        counter_            = 0;
        constructor_counter_        = 0;
        dtor_counter_        = 0;
        default_constructor_counter_ = 0;
        arg_constructor_counter_     = 0;
        copy_constructor_counter_    = 0;
        move_constructor_counter_    = 0;
        copy_assign_counter_  = 0;
        move_assign_counter_  = 0;
        magic_error_counter_    = 0;
    }

    static bool is_clear() {
        return (counter_ == 0) && (dtor_counter_ == constructor_counter_) && (magic_error_counter_ == 0);
    }
};

int64_t big_object::counter_              = 0;
int64_t big_object::constructor_counter_         = 0;
int64_t big_object::dtor_counter_         = 0;
int64_t big_object::default_constructor_counter_ = 0;
int64_t big_object::arg_constructor_counter_     = 0;
int64_t big_object::copy_constructor_counter_    = 0;
int64_t big_object::move_constructor_counter_    = 0;
int64_t big_object::copy_assign_counter_  = 0;
int64_t big_object::move_assign_counter_  = 0;
int     big_object::magic_error_counter_   = 0;

struct small_object final {
    static int constructor_counter_;

    small_object() noexcept { constructor_counter_++; }
    small_object(const small_object&) noexcept { constructor_counter_++; }
    small_object(small_object&&) noexcept { constructor_counter_++; }
    small_object& operator=(const small_object&) noexcept { constructor_counter_++; return *this; }
    ~small_object() noexcept { constructor_counter_--; }

    static void reset() { constructor_counter_ = 0; }
    static bool is_clear() { return constructor_counter_ == 0; }
};

int small_object::constructor_counter_ = 0;


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
        big_object::reset();
        { any a{big_object()}; }
        assert(!big_object::is_clear());
    }

    {
        small_object::reset();
        { any a{small_object()}; }
        assert(small_object::is_clear());
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
        std::vector<any> va = {42, std::string("ted"), 'a', 42.f};
        assert(any_cast<int>(va[0]) == 42);
        assert(any_cast<std::string>(va[1]) == "ted");
        assert(any_cast<char>(va[2]) == 'a');
        assert(any_cast<float>(va[3]) == 42.f);
    }

    {
        std::vector<any> va;
        va.push_back(42);
        va.push_back(std::string("ted"));
        va.push_back('a');
        va.push_back(42.f);

        assert(any_cast<int>(va[0]) == 42);
        assert(any_cast<std::string>(va[1]) == "ted");
        assert(any_cast<char>(va[2]) == 'a');
        assert(any_cast<float>(va[3]) == 42.f);
    }

    {
        big_object::reset();
        {
            std::vector<any> va = {42, 'a', 42.f, 3333u, 4444ul, 5555ull, 6666.0};

            assert(any_cast<int>(va[0]) == 42);
            assert(any_cast<char>(va[1]) == 'a');
            assert(any_cast<float>(va[2]) == 42.f);
            assert(any_cast<unsigned>(va[3]) == 3333u);
            assert(any_cast<unsigned long>(va[4]) == 4444ul);
            assert(any_cast<unsigned long long>(va[5]) == 5555ull);
            assert(any_cast<double>(va[6]) == 6666.0);

            va[3] = big_object(3333);

            assert(any_cast<int>(va[0]) == 42);
            assert(any_cast<char>(va[1]) == 'a');
            assert(any_cast<float>(va[2]) == 42.f);
            assert(any_cast<big_object>(va[3]).x_ == 3333);
            assert(any_cast<unsigned long>(va[4]) == 4444ul);
            assert(any_cast<unsigned long long>(va[5]) == 5555ull);
            assert(any_cast<double>(va[6]) == 6666.0);
        }
        assert(!big_object::is_clear());
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
        big_object::reset();
        {
            any a;
            a.emplace<big_object>();
            assert(a.has_value());
        }
        assert(!big_object::is_clear());
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