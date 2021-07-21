#pragma once

#include "type_id.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <type_traits>

#define TEST_NOEXCEPT noexcept

struct AllocController;
// 'AllocController' is a concrete type that instruments and controls the
// behavior of test allocators.

template<class T, size_t ID = 0>
class CountingAllocator;
// 'CountingAllocator' is an basic implementation of the 'Allocator'
// requirements that use the 'AllocController' interface.

template<class T>
class MinAlignAllocator;
// 'MinAlignAllocator' is an instrumented test type which implements the
// 'Allocator' requirements. 'MinAlignAllocator' ensures that it *never*
// returns a pointer to over-aligned storage. For example
// 'MinAlignPointer<char>{}.allocate(...)' will never a 2-byte aligned
// pointer.

template<class T>
class NullAllocator;
// 'NullAllocator' is an instrumented test type which implements the
// 'Allocator' requirements except that 'allocator' and 'deallocate' are
// nops.

#define DISALLOW_COPY(Type)     \
    Type(Type const&) = delete; \
    Type& operator=(Type const&) = delete

constexpr std::size_t MaxAlignV = alignof(std::max_align_t);

struct TestException {};

struct AllocController {
    int copy_constructed = 0;
    int move_constructed = 0;

    int alive = 0;
    int alloc_count = 0;
    int dealloc_count = 0;
    int is_equal_count = 0;

    std::size_t alive_size;
    std::size_t allocated_size;
    std::size_t deallocated_size;

    std::size_t last_size = 0;
    std::size_t last_align = 0;
    void* last_pointer = 0;

    std::size_t last_alloc_size = 0;
    std::size_t last_alloc_align = 0;
    void* last_alloc_pointer = nullptr;

    std::size_t last_dealloc_size = 0;
    std::size_t last_dealloc_align = 0;
    void* last_dealloc_pointer = nullptr;

    bool throw_on_alloc = false;

    int construct_called = 0;
    void* last_construct_pointer = nullptr;
    TypeID const* last_construct_alloc = nullptr;
    TypeID const* last_construct_type = nullptr;
    TypeID const* last_construct_args = nullptr;

    int destroy_called = 0;
    void* last_destroy_pointer = nullptr;
    TypeID const* last_destroy_alloc = nullptr;
    TypeID const* last_destroy_type = nullptr;

    AllocController() = default;

    void countAlloc(void* p, size_t s, size_t a) {
        ++alive;
        ++alloc_count;
        alive_size += s;
        allocated_size += s;
        last_pointer = last_alloc_pointer = p;
        last_size = last_alloc_size = s;
        last_align = last_alloc_align = a;
    }

    void countDealloc(void* p, size_t s, size_t a) {
        --alive;
        ++dealloc_count;
        alive_size -= s;
        deallocated_size += s;
        last_pointer = last_dealloc_pointer = p;
        last_size = last_dealloc_size = s;
        last_align = last_dealloc_align = a;
    }

    template<class... Args, class Alloc, class Tp>
    void countConstruct(Alloc const&, Tp* p) {
        ++construct_called;
        last_construct_pointer = p;
        last_construct_alloc = &makeTypeID<Alloc>();
        last_construct_type = &makeTypeID<Tp>();
        last_construct_args = &makeArgumentID<Args...>();
    }

    template<class Alloc, class Tp>
    void countDestroy(Alloc const&, Tp* p) {
        ++destroy_called;
        last_destroy_alloc = &makeTypeID<Alloc>();
        last_destroy_type = &makeTypeID<Tp>();
        last_destroy_pointer = p;
    }

    void reset() { std::memset(this, 0, sizeof(*this)); }
    void resetConstructDestroy() {
        construct_called = 0;
        last_construct_pointer = nullptr;
        last_construct_alloc = last_construct_args = last_construct_type = nullptr;
        destroy_called = 0;
        last_destroy_alloc = nullptr;
        last_destroy_pointer = nullptr;
    }

public:
    bool checkAlloc(void* p, size_t s, size_t a) const {
        return p == last_alloc_pointer &&
               s == last_alloc_size &&
               a == last_alloc_align;
    }

    bool checkAlloc(void* p, size_t s) const {
        return p == last_alloc_pointer &&
               s == last_alloc_size;
    }

    bool checkAllocAtLeast(void* p, size_t s, size_t a) const {
        return p == last_alloc_pointer &&
               s <= last_alloc_size &&
               a <= last_alloc_align;
    }

    bool checkAllocAtLeast(void* p, size_t s) const {
        return p == last_alloc_pointer &&
               s <= last_alloc_size;
    }

    bool checkDealloc(void* p, size_t s, size_t a) const {
        return p == last_dealloc_pointer &&
               s == last_dealloc_size &&
               a == last_dealloc_align;
    }

    bool checkDealloc(void* p, size_t s) const {
        return p == last_dealloc_pointer &&
               s == last_dealloc_size;
    }

    bool checkDeallocMatchesAlloc() const {
        return last_dealloc_pointer == last_alloc_pointer &&
               last_dealloc_size == last_alloc_size &&
               last_dealloc_align == last_alloc_align;
    }

    template<class... Args, class Alloc, class Tp>
    bool checkConstruct(Alloc const&, Tp* p) const {
        auto expectAlloc = &makeTypeID<Alloc>();
        auto expectTp = &makeTypeID<Tp>();
        auto expectArgs = &makeArgumentID<Args...>();
        return last_construct_pointer == p &&
               COMPARE_TYPEID(last_construct_alloc, expectAlloc) &&
               COMPARE_TYPEID(last_construct_type, expectTp) &&
               COMPARE_TYPEID(last_construct_args, expectArgs);
    }

    template<class Alloc, class Tp>
    bool checkDestroy(Alloc const&, Tp* p) const {
        return last_destroy_pointer == p &&
               last_destroy_alloc == &makeTypeID<Alloc>() &&
               last_destroy_type == &makeTypeID<Tp>();
    }

    bool checkDestroyMatchesConstruct() const {
        return last_destroy_pointer == last_construct_pointer &&
               last_destroy_type == last_construct_type;
    }

    void countIsEqual() {
        ++is_equal_count;
    }

    bool checkIsEqualCalledEq(int n) const {
        return is_equal_count == n;
    }

private:
    DISALLOW_COPY(AllocController);
};

template<class T, size_t ID>
class CountingAllocator {
public:
    typedef T value_type;
    typedef T* pointer;

    template<class U>
    struct rebind { using other = CountingAllocator<U, ID>; };

    CountingAllocator() = delete;
    explicit CountingAllocator(AllocController& PP)
        : P(&PP) {}

    CountingAllocator(CountingAllocator const& other)
        : P(other.P) {
        P->copy_constructed += 1;
    }

    CountingAllocator(CountingAllocator&& other)
        : P(other.P) {
        P->move_constructed += 1;
    }

    template<class U>
    CountingAllocator(CountingAllocator<U, ID> const& other) TEST_NOEXCEPT : P(other.P) {
        P->copy_constructed += 1;
    }

    template<class U>
    CountingAllocator(CountingAllocator<U, ID>&& other) TEST_NOEXCEPT : P(other.P) {
        P->move_constructed += 1;
    }

    T* allocate(std::size_t n) {
        void* ret = ::operator new(n * sizeof(T));
        P->countAlloc(ret, n * sizeof(T), alignof(T));
        return static_cast<T*>(ret);
    }

    void deallocate(T* p, std::size_t n) {
        void* vp = static_cast<void*>(p);
        P->countDealloc(vp, n * sizeof(T), alignof(T));
        ::operator delete(vp);
    }

    template<class U, class... Args>
    void construct(U* p, Args&&... args) {
        ::new ((void*) p) U(std::forward<Args>(args)...);
        P->countConstruct<Args&&...>(*this, p);
    }

    template<class U>
    void destroy(U* p) {
        p->~U();
        P->countDestroy(*this, p);
    }

    AllocController& getController() const { return *P; }

private:
    template<class Tp, size_t XID>
    friend class CountingAllocator;
    AllocController* P;
};

template<size_t ID>
class CountingAllocator<void, ID> {
public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;

    template<class U>
    struct rebind { using other = CountingAllocator<U, ID>; };

    CountingAllocator() = delete;
    explicit CountingAllocator(AllocController& PP)
        : P(&PP) {}

    CountingAllocator(CountingAllocator const& other)
        : P(other.P) {
        P->copy_constructed += 1;
    }

    CountingAllocator(CountingAllocator&& other)
        : P(other.P) {
        P->move_constructed += 1;
    }

    template<class U>
    CountingAllocator(CountingAllocator<U, ID> const& other) TEST_NOEXCEPT : P(other.P) {
        P->copy_constructed += 1;
    }

    template<class U>
    CountingAllocator(CountingAllocator<U, ID>&& other) TEST_NOEXCEPT : P(other.P) {
        P->move_constructed += 1;
    }

    void construct(...) = delete;
    void destroy(void*) = delete;

    AllocController& getController() const { return *P; }

private:
    template<class Tp, size_t>
    friend class CountingAllocator;
    AllocController* P;
};

template<class T, class U, size_t ID>
inline bool operator==(CountingAllocator<T, ID> const& x,
                       CountingAllocator<U, ID> const& y) {
    return &x.getController() == &y.getController();
}

template<class T, class U, size_t ID>
inline bool operator!=(CountingAllocator<T, ID> const& x,
                       CountingAllocator<U, ID> const& y) {
    return !(x == y);
}

template<class T>
class NullAllocator {
public:
    typedef T value_type;
    typedef T* pointer;
    NullAllocator() = delete;
    explicit NullAllocator(AllocController& PP)
        : P(&PP) {}

    NullAllocator(NullAllocator const& other)
        : P(other.P) {
        P->copy_constructed += 1;
    }

    NullAllocator(NullAllocator&& other)
        : P(other.P) {
        P->move_constructed += 1;
    }

    template<class U>
    NullAllocator(NullAllocator<U> const& other) TEST_NOEXCEPT : P(other.P) {
        P->copy_constructed += 1;
    }

    template<class U>
    NullAllocator(NullAllocator<U>&& other) TEST_NOEXCEPT : P(other.P) {
        P->move_constructed += 1;
    }

    T* allocate(std::size_t n) {
        P->countAlloc(nullptr, n * sizeof(T), alignof(T));
        return nullptr;
    }

    void deallocate(T* p, std::size_t n) {
        void* vp = static_cast<void*>(p);
        P->countDealloc(vp, n * sizeof(T), alignof(T));
    }

    AllocController& getController() const { return *P; }

private:
    template<class Tp>
    friend class NullAllocator;
    AllocController* P;
};

template<class T, class U>
inline bool operator==(NullAllocator<T> const& x,
                       NullAllocator<U> const& y) {
    return &x.getController() == &y.getController();
}

template<class T, class U>
inline bool operator!=(NullAllocator<T> const& x,
                       NullAllocator<U> const& y) {
    return !(x == y);
}
