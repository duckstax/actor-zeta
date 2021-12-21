#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#define TEST_HAS_NO_EXCEPTIONS

#include "classes.hpp"

TEST_CASE("memory.resource.eq") {
    SECTION("equal.pass") {
        // check return types
        {
            memory_resource const* mr1(nullptr);
            memory_resource const* mr2(nullptr);
            REQUIRE(std::is_same<decltype(*mr1 == *mr2), bool>::value);
            REQUIRE(noexcept(*mr1 == *mr2));
        }
        // equal
        {
            test_resource_t r1(1);
            test_resource_t r2(1);
            memory_resource const& mr1 = r1;
            memory_resource const& mr2 = r2;
            REQUIRE(mr1 == mr2);
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(0));
            REQUIRE(mr2 == mr1);
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(1));
        }
        // equal same object
        {
            test_resource_t r1(1);
            memory_resource const& mr1 = r1;
            memory_resource const& mr2 = r1;
            REQUIRE(mr1 == mr2);
            REQUIRE(r1.check_is_equal_called_eq(0));
            REQUIRE(mr2 == mr1);
            REQUIRE(r1.check_is_equal_called_eq(0));
        }
        // not equal
        {
            test_resource_t r1(1);
            test_resource_t r2(2);
            memory_resource const& mr1 = r1;
            memory_resource const& mr2 = r2;
            REQUIRE(!(mr1 == mr2));
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(0));
            REQUIRE(!(mr2 == mr1));
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(1));
        }
    }

    SECTION("not_equal.pass") {
        // check return types
        {
            memory_resource const* mr1(nullptr);
            memory_resource const* mr2(nullptr);
            REQUIRE(std::is_same<decltype(*mr1 != *mr2), bool>::value);
            REQUIRE(noexcept(*mr1 != *mr2));
        }
        // not equal
        {
            test_resource_t r1(1);
            test_resource_t r2(2);
            memory_resource const& mr1 = r1;
            memory_resource const& mr2 = r2;
            REQUIRE(mr1 != mr2);
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(0));
            REQUIRE(mr2 != mr1);
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(1));
        }
        // equal
        {
            test_resource_t r1(1);
            test_resource_t r2(1);
            memory_resource const& mr1 = r1;
            memory_resource const& mr2 = r2;
            REQUIRE(!(mr1 != mr2));
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(0));
            REQUIRE(!(mr2 != mr1));
            REQUIRE(r1.check_is_equal_called_eq(1));
            REQUIRE(r2.check_is_equal_called_eq(1));
        }
        // equal same object
        {
            test_resource_t r1(1);
            memory_resource const& mr1 = r1;
            memory_resource const& mr2 = r1;
            REQUIRE(!(mr1 != mr2));
            REQUIRE(r1.check_is_equal_called_eq(0));
            REQUIRE(!(mr2 != mr1));
            REQUIRE(r1.check_is_equal_called_eq(0));
        }
    }
}

TEST_CASE("memory.resource.public") {
    SECTION("allocate.pass") {
        test_resource_t R(42);
        auto& P = R.get_controller();
        memory_resource& M = R;
        {
            REQUIRE(std::is_same<decltype(M.allocate(0, 0)), void*>::value);
            REQUIRE(std::is_same<decltype(M.allocate(0)), void*>::value);
        }
        {
            REQUIRE(!noexcept(M.allocate(0, 0)));
            REQUIRE(!noexcept(M.allocate(0)));
        }
        {
            std::size_t s = 42;
            std::size_t a = 64;
            void* p = M.allocate(s, a);
            REQUIRE(P.alloc_count == 1);
            REQUIRE(P.check_alloc(p, s, a));
            s = 128;
            a = MaxAlignV;
            p = M.allocate(s);
            REQUIRE(P.alloc_count == 2);
            REQUIRE(P.check_alloc(p, s, a));
        }
#ifndef TEST_HAS_NO_EXCEPTIONS
        {
            test_resource_t R2;
            auto& P = R2.get_controller();
            P.throw_on_alloc = true;
            memory_resource& M2 = R2;
            try {
                M2.allocate(42);
                REQUIRE(false);
            } catch (test_exception_t const&) {
                // do nothing.
            } catch (...) {
                REQUIRE(false);
            }
        }
#endif
    }

    SECTION("deallocate.pass") {
        null_resource_t R(42);
        auto& P = R.get_controller();
        memory_resource& M = R;
        {
            REQUIRE(std::is_same<decltype(M.deallocate(nullptr, 0, 0)), void>::value);
            REQUIRE(std::is_same<decltype(M.deallocate(nullptr, 0)), void>::value);
        }
        {
            REQUIRE(!noexcept(M.deallocate(nullptr, 0, 0)));
            REQUIRE(!noexcept(M.deallocate(nullptr, 0)));
        }
        {
            std::size_t s = 100;
            std::size_t a = 64;
            void* p = reinterpret_cast<void*>(640);
            M.deallocate(p, s, a);
            REQUIRE(P.dealloc_count == 1);
            REQUIRE(P.check_dealloc(p, s, a));
            s = 128;
            a = alignof(::max_align_t);
            p = reinterpret_cast<void*>(12800);
            M.deallocate(p, s);
            REQUIRE(P.dealloc_count == 2);
            REQUIRE(P.check_dealloc(p, s, a));
        }
    }

    SECTION("dtor.pass") {
        REQUIRE(std::has_virtual_destructor<memory_resource>::value);
        REQUIRE(std::is_nothrow_destructible<memory_resource>::value);
        REQUIRE(std::is_abstract<memory_resource>::value);
        // Check that the destructor of `test_resource_t` is called when
        // it is deleted as a pointer to `memory_resource`
        {
            using TR = test_resource_t;
            TR::reset_statics();
            memory_resource* M = new TR(42);
            REQUIRE(TR::resource_alive == 1);
            REQUIRE(TR::resource_constructed == 1);
            REQUIRE(TR::resource_destructed == 0);
            delete M;
            REQUIRE(TR::resource_alive == 0);
            REQUIRE(TR::resource_constructed == 1);
            REQUIRE(TR::resource_destructed == 1);
        }
    }

    SECTION("is_equal.pass") {
        {
            memory_resource const* r1 = nullptr;
            memory_resource const* r2 = nullptr;
            REQUIRE(noexcept(r1->is_equal(*r2)));
        }
        {
            test_resource1_t R1(1);
            auto& P1 = R1.get_controller();
            memory_resource const& M1 = R1;
            test_resource2_t R2(1);
            auto& P2 = R2.get_controller();
            memory_resource const& M2 = R2;
            REQUIRE(M1.is_equal(M2) == false);
            REQUIRE(P1.check_is_equal_called_eq(1));
            REQUIRE(P2.check_is_equal_called_eq(0));
            REQUIRE(M2.is_equal(M1) == false);
            REQUIRE(P2.check_is_equal_called_eq(1));
            REQUIRE(P1.check_is_equal_called_eq(1));
        }
        {
            test_resource1_t R1(1);
            auto& P1 = R1.get_controller();
            memory_resource const& M1 = R1;
            test_resource1_t R2(2);
            auto& P2 = R2.get_controller();
            memory_resource const& M2 = R2;
            REQUIRE(M1.is_equal(M2) == false);
            REQUIRE(P1.check_is_equal_called_eq(1));
            REQUIRE(P2.check_is_equal_called_eq(0));
            REQUIRE(M2.is_equal(M1) == false);
            REQUIRE(P2.check_is_equal_called_eq(1));
            REQUIRE(P1.check_is_equal_called_eq(1));
        }
        {
            test_resource1_t R1(1);
            auto& P1 = R1.get_controller();
            memory_resource const& M1 = R1;
            test_resource1_t R2(1);
            auto& P2 = R2.get_controller();
            memory_resource const& M2 = R2;
            REQUIRE(M1.is_equal(M2) == true);
            REQUIRE(P1.check_is_equal_called_eq(1));
            REQUIRE(P2.check_is_equal_called_eq(0));
            REQUIRE(M2.is_equal(M1) == true);
            REQUIRE(P2.check_is_equal_called_eq(1));
            REQUIRE(P1.check_is_equal_called_eq(1));
        }
    }
}

#if CPP17_OR_GREATER
TEST_CASE("construct_piecewise_pair.pass") {
    SECTION("1") {
        using T = count_copies_t;
        using U = count_copies_alloc_v1_t;
        using P = std::pair<T, U>;

        std::tuple<T> t1;
        std::tuple<U> t2;

        test_harness_t<P> h;
        h.construct(std::piecewise_construct, t1, t2);
        P const& p = *h.ptr;
        REQUIRE(p.first.count == 2);
        REQUIRE(p.second.count == 2);
        REQUIRE(p.second.alloc == h.M);
    }

    SECTION("2") {
        using T = count_copies_alloc_v1_t;
        using U = count_copies_alloc_v2_t;
        using P = std::pair<T, U>;

        std::tuple<T> t1;
        std::tuple<U> t2;

        test_harness_t<P> h;
        h.construct(std::piecewise_construct, std::move(t1), std::move(t2));
        P const& p = *h.ptr;
        REQUIRE(p.first.count == 2);
        REQUIRE(p.first.alloc == h.M);
        REQUIRE(p.second.count == 2);
        REQUIRE(p.second.alloc == h.M);
    }

    SECTION("3") {
        using T = count_copies_alloc_v2_t;
        using U = count_copies_alloc_v1_t;
        using P = std::pair<T, U>;

        std::tuple<T> t1;
        std::tuple<U> t2;

        test_harness_t<P> h;
        h.construct(std::piecewise_construct, std::move(t1), std::move(t2));
        P const& p = *h.ptr;
        REQUIRE(p.first.count == 2);
        REQUIRE(p.first.alloc == h.M);
        REQUIRE(p.second.count == 2);
        REQUIRE(p.second.alloc == h.M);
    }

    SECTION("4") {
        using T = count_copies_alloc_v2_t;
        using U = count_copies_t;
        using P = std::pair<T, U>;

        std::tuple<T> t1;
        std::tuple<U> t2;

        test_harness_t<P> h;
        h.construct(std::piecewise_construct, t1, t2);
        P const& p = *h.ptr;
        REQUIRE(p.first.count == 2);
        REQUIRE(p.first.alloc == h.M);
        REQUIRE(p.second.count == 2);
    }
}
#endif

TEST_CASE("memory.polymorphic.allocator.ctor") {
    /*SECTION("assign.pass") { // fails on gcc-11, gcc, 11, g++-11, Debug, 17
        typedef polymorphic_allocator<void> T;
        REQUIRE(std::is_copy_assignable<T>::value);
        REQUIRE(std::is_move_assignable<T>::value);
    }*/

    SECTION("copy.pass") {
        typedef polymorphic_allocator<void> A1;
        {
            REQUIRE(std::is_copy_constructible<A1>::value);
            REQUIRE(std::is_move_constructible<A1>::value);
        }
        // copy
        {
            A1 const a(reinterpret_cast<memory_resource*>(42));
            A1 const a2(a);
            REQUIRE(a.resource() == a2.resource());
        }
        // move
        {
            A1 a(reinterpret_cast<memory_resource*>(42));
            A1 a2(std::move(a));
            REQUIRE(a.resource() == a2.resource());
            REQUIRE(a2.resource() == reinterpret_cast<memory_resource*>(42));
        }
    }

    SECTION("default.pass") {
        {
            REQUIRE(std::is_nothrow_default_constructible<polymorphic_allocator<void>>::value);
        }
        {
            // test that the allocator gets its resource from get_default_resource
            test_resource_t R1(42);
            pmr::set_default_resource(&R1);
            typedef polymorphic_allocator<void> A;
            A const a;
            REQUIRE(a.resource() == &R1);
            pmr::set_default_resource(nullptr);
            A const a2;
            REQUIRE(a.resource() == &R1);
            REQUIRE(a2.resource() == pmr::new_delete_resource());
        }
    }

    SECTION("memory_resource_convert.pass") {
        {
            typedef polymorphic_allocator<void> A;
            REQUIRE(std::is_convertible<decltype(nullptr), A>::value);
            REQUIRE(std::is_convertible<memory_resource*, A>::value);
        }
        {
            typedef polymorphic_allocator<void> A;
            test_resource_t R;
            A const a(&R);
            REQUIRE(a.resource() == &R);
        }
    }

    SECTION("other_alloc.pass") {
        typedef polymorphic_allocator<void> A1;
        typedef polymorphic_allocator<char> A2;
        { // Test that the conversion is implicit and noexcept.
            REQUIRE(std::is_convertible<A1 const&, A2>::value);
            REQUIRE(std::is_convertible<A2 const&, A1>::value);
            REQUIRE(std::is_nothrow_constructible<A1, A2 const&>::value);
            REQUIRE(std::is_nothrow_constructible<A2, A1 const&>::value);
        }
        // copy other type
        {
            A1 const a(reinterpret_cast<memory_resource*>(42));
            A2 const a2(a);
            REQUIRE(a.resource() == a2.resource());
            REQUIRE(a2.resource() == reinterpret_cast<memory_resource*>(42));
        }
        {
            A1 a(reinterpret_cast<memory_resource*>(42));
            A2 const a2(std::move(a));
            REQUIRE(a.resource() == a2.resource());
            REQUIRE(a2.resource() == reinterpret_cast<memory_resource*>(42));
        }
    }
}

TEST_CASE("memory.polymorphic.allocator.eq") {
    SECTION("equal.pass") {
        typedef polymorphic_allocator<void> A1;
        typedef polymorphic_allocator<int> A2;
        // check return types
        {
            A1 const a1;
            A2 const a2;
            REQUIRE(std::is_same<decltype(a1 == a2), bool>::value);
            REQUIRE(noexcept(a1 == a2));
        }
        // equal same type (different resource)
        {
            test_resource_t d1(1);
            test_resource_t d2(1);
            A1 const a1(&d1);
            A1 const a2(&d2);
            REQUIRE(a1 == a2);
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(0));
            d1.reset();
            REQUIRE(a2 == a1);
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(d2.check_is_equal_called_eq(1));
        }
        // equal same type (same resource)
        {
            test_resource_t d1;
            A1 const a1(&d1);
            A1 const a2(&d1);
            REQUIRE(a1 == a2);
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(a2 == a1);
            REQUIRE(d1.check_is_equal_called_eq(0));
        }
        // equal different type (different resource)
        {
            test_resource_t d1(42);
            test_resource_t d2(42);
            A1 const a1(&d1);
            A2 const a2(&d2);
            REQUIRE(a1 == a2);
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(0));
            REQUIRE(a2 == a1);
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(1));
        }
        // equal different type (same resource)
        {
            test_resource_t d1(42);
            A1 const a1(&d1);
            A2 const a2(&d1);
            REQUIRE(a1 == a2);
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(a2 == a1);
            REQUIRE(d1.check_is_equal_called_eq(0));
        }
        // not equal same type
        {
            test_resource_t d1(1);
            test_resource_t d2(2);
            A1 const a1(&d1);
            A1 const a2(&d2);
            REQUIRE(!(a1 == a2));
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(0));
            d1.reset();
            REQUIRE(!(a2 == a1));
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(d2.check_is_equal_called_eq(1));
        }
        // not equal different types
        {
            test_resource_t d1;  // value 0 type 0
            test_resource1_t d2; // value 0 type 1
            A1 const a1(&d1);
            A2 const a2(&d2);
            REQUIRE(!(a1 == a2));
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(0));
            d1.reset();
            REQUIRE(!(a2 == a1));
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(d2.check_is_equal_called_eq(1));
        }
    }

    SECTION("not_equal.pass") {
        typedef polymorphic_allocator<void> A1;
        typedef polymorphic_allocator<int> A2;
        // check return types
        {
            A1 const a1;
            A2 const a2;
            REQUIRE(std::is_same<decltype(a1 != a2), bool>::value);
            REQUIRE(noexcept(a1 != a2));
        }
        // not equal same type (different resource)
        {
            test_resource_t d1(1);
            test_resource_t d2(2);
            A1 const a1(&d1);
            A1 const a2(&d2);
            REQUIRE(a1 != a2);
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(0));
            d1.reset();
            REQUIRE(a2 != a1);
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(d2.check_is_equal_called_eq(1));
        }
        // equal same type (same resource)
        {
            test_resource_t d1;
            A1 const a1(&d1);
            A1 const a2(&d1);
            REQUIRE(!(a1 != a2));
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(!(a2 != a1));
            REQUIRE(d1.check_is_equal_called_eq(0));
        }
        // equal same type
        {
            test_resource_t d1(1);
            test_resource_t d2(1);
            A1 const a1(&d1);
            A1 const a2(&d2);
            REQUIRE(!(a1 != a2));
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(0));
            d1.reset();
            REQUIRE(!(a2 != a1));
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(d2.check_is_equal_called_eq(1));
        }
        // not equal different types
        {
            test_resource_t d1;  // value 0 type 0
            test_resource1_t d2; // value 0 type 1
            A1 const a1(&d1);
            A2 const a2(&d2);
            REQUIRE(a1 != a2);
            REQUIRE(d1.check_is_equal_called_eq(1));
            REQUIRE(d2.check_is_equal_called_eq(0));
            d1.reset();
            REQUIRE(a2 != a1);
            REQUIRE(d1.check_is_equal_called_eq(0));
            REQUIRE(d2.check_is_equal_called_eq(1));
        }
    }
}

template<size_t S, size_t Align>
void testForSizeAndAlign() {
    using T = typename std::aligned_storage<S, Align>::type;
    test_resource_t R;
    polymorphic_allocator<T> a(&R);
    for (std::size_t N = 1; N <= 5; ++N) {
        auto ret = a.allocate(N);
        REQUIRE(R.check_alloc(ret, N * sizeof(T), alignof(T)));
        a.deallocate(ret, N);
        R.reset();
    }
}

TEST_CASE("memory.polymorphic.allocator.mem") {
    SECTION("allocate.pass") {
        {
            polymorphic_allocator<int> a;
            REQUIRE(std::is_same<decltype(a.allocate(0)), int*>::value);
            REQUIRE(!noexcept(a.allocate(0)));
        }
        {
            constexpr std::size_t MA = alignof(::max_align_t);
            testForSizeAndAlign<1, 1>();
            testForSizeAndAlign<1, 2>();
            testForSizeAndAlign<1, MA>();
            testForSizeAndAlign<2, 2>();
            testForSizeAndAlign<73, alignof(void*)>();
            testForSizeAndAlign<73, MA>();
            testForSizeAndAlign<13, MA>();
        }
    }

    SECTION("construct_pair.pass") {
        typedef default_constructible T;
        typedef std::pair<T, T> P;
        typedef polymorphic_allocator<void> A;
        P* ptr = (P*) std::malloc(sizeof(P));
        A a;
        a.construct(ptr);
        REQUIRE(default_constructible::constructed == 2);
        REQUIRE(ptr->first.x == 42);
        REQUIRE(ptr->second.x == 42);
        std::free(ptr);
    }

    SECTION("destroy.pass") {
        typedef polymorphic_allocator<double> A;
        {
            A a;
            REQUIRE(std::is_same<decltype(a.destroy((destroyable*) nullptr)), void>::value);
        }
        {
            destroyable* ptr = ::new (std::malloc(sizeof(destroyable))) destroyable();
            REQUIRE(destroyable::count == 1);
            A{}.destroy(ptr);
            REQUIRE(destroyable::count == 0);
            std::free(ptr);
        }
    }

    SECTION("resource.pass") {
        typedef polymorphic_allocator<void> A;
        {
            A const a;
            REQUIRE(std::is_same<decltype(a.resource()), memory_resource*>::value);
        }
        {
            memory_resource* mptr = reinterpret_cast<memory_resource*>(42);
            A const a(mptr);
            REQUIRE(a.resource() == mptr);
        }
        {
            A const a(nullptr);
            REQUIRE(a.resource() == nullptr);
            REQUIRE(a.resource() == nullptr);
        }
        {
            A const a;
            REQUIRE(a.resource() == pmr::get_default_resource());
        }
        {
            memory_resource* mptr = reinterpret_cast<memory_resource*>(42);
            pmr::set_default_resource(mptr);
            A const a;
            REQUIRE(a.resource() == mptr);
            REQUIRE(a.resource() == pmr::get_default_resource());
        }
    }

    SECTION("select_on_container_copy_construction.pass") {
        typedef polymorphic_allocator<void> A;
        {
            A const a;
            REQUIRE(std::is_same<decltype(a.select_on_container_copy_construction()), A>::value);
        }
        {
            memory_resource* mptr = reinterpret_cast<memory_resource*>(42);
            A const a(mptr);
            REQUIRE(a.resource() == mptr);
            A const other = a.select_on_container_copy_construction();
            REQUIRE(other.resource() == pmr::get_default_resource());
            REQUIRE(a.resource() == mptr);
        }
        {
            memory_resource* mptr = reinterpret_cast<memory_resource*>(42);
            pmr::set_default_resource(mptr);
            A const a;
            REQUIRE(a.resource() == pmr::get_default_resource());
            A const other = a.select_on_container_copy_construction();
            REQUIRE(other.resource() == pmr::get_default_resource());
            REQUIRE(other.resource() == mptr);
            REQUIRE(a.resource() == pmr::get_default_resource());
        }
        {
            memory_resource* mptr = reinterpret_cast<memory_resource*>(42);
            pmr::set_default_resource(mptr);
            A const a(nullptr);
            REQUIRE(a.resource() == nullptr);
            A const other = a.select_on_container_copy_construction();
            REQUIRE(other.resource() == pmr::get_default_resource());
            REQUIRE(other.resource() == mptr);
            REQUIRE(a.resource() == nullptr);
        }
    }
}

TEST_CASE("polymorphic_allocator") {
    REQUIRE(std::is_destructible<test_type>{});
    REQUIRE(std::is_copy_constructible<test_type>{});
    ///REQUIRE(std::is_copy_assignable<test_type>{}); ///TODO: hack
    REQUIRE(std::is_constructible<test_type, memory_resource*>{});
    REQUIRE(!std::is_polymorphic<test_type>{});
#if CPP17_OR_GREATER or CPP14_OR_GREATER
    REQUIRE(!std::is_final<test_type>{});
#endif
    SECTION("resource_constructor") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> b(&d);
        REQUIRE(&d == b.resource());
    }

    SECTION("copy_constructor") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> b(&d);
        polymorphic_allocator<int> c(b);
        REQUIRE(b.resource() == c.resource());
    }

    SECTION("copy_assignment") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> b(&d);
        auto c = b;
        REQUIRE(c.resource() == b.resource());
    }

    SECTION("allocate") {
        int dummy;
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        d.reset();
        d.do_allocate_return = &dummy;
        p.allocate(2);
        REQUIRE(d.do_allocate_called == true);
        REQUIRE(d.do_allocate_return == &dummy);
        //It shall allocate 2*sizeof(int), alignment_of<int>
        REQUIRE(d.do_allocate_bytes == 2 * sizeof(int));
        REQUIRE(d.do_allocate_alignment == std::alignment_of<int>::value);
    }

    SECTION("deallocate") {
        int dummy;
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        d.reset();
        p.deallocate(&dummy, 3);
        REQUIRE(d.do_deallocate_called == true);
        //It shall deallocate 2*sizeof(int), alignment_of<int>
        REQUIRE(d.do_deallocate_p == &dummy);
        REQUIRE(d.do_deallocate_bytes == 3 * sizeof(int));
        REQUIRE(d.do_deallocate_alignment == std::alignment_of<int>::value);
    }

    SECTION("construct") {
        {
            std::array<int, 3> value;
            derived_from_memory_resource d;
            polymorphic_allocator<int> pa(&d);
            pa.construct(&value);
        }
        {
            // using value_type = x; // forbids type aliasing here
            x value;
            value.~x(); // this call must use the original name
            derived_from_memory_resource d;
            polymorphic_allocator<int> pa(&d);
            pa.construct(&value);
            REQUIRE(value.value_ == 0);
            value.~x();
        }
        {
            // using value_type = x; // forbids type aliasing here
            x value;
            value.~x(); // this call must use the original name
            derived_from_memory_resource d;
            polymorphic_allocator<int> pa(&d);
            pa.construct(&value, 2);
            REQUIRE(value.value_ == 2);
            value.~x();
        }
    }

    SECTION("destroy") {
        char_holder ch;
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        REQUIRE(char_holder::destructor_called == false);
        p.destroy(&ch);
        REQUIRE(char_holder::destructor_called == true);
    }

    SECTION("resource") {
        derived_from_memory_resource d;
        polymorphic_allocator<int> p(&d);
        REQUIRE(&d == p.resource());
    }
}
