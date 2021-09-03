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

struct alloc_controller_t;

template<class T, size_t ID = 0>
class counting_allocator_t;

template<class T>
class min_align_allocator_t;

template<class T>
class null_allocator_t;

#define DISALLOW_COPY(Type)     \
    Type(Type const&) = delete; \
    Type& operator=(Type const&) = delete

constexpr std::size_t MaxAlignV = alignof(::max_align_t);

struct test_exception_t {};

struct alloc_controller_t {
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
    type_id_t const* last_construct_alloc = nullptr;
    type_id_t const* last_construct_type = nullptr;
    type_id_t const* last_construct_args = nullptr;

    int destroy_called = 0;
    void* last_destroy_pointer = nullptr;
    type_id_t const* last_destroy_alloc = nullptr;
    type_id_t const* last_destroy_type = nullptr;

    alloc_controller_t() = default;

    void count_alloc(void* p, size_t s, size_t a) {
        ++alive;
        ++alloc_count;
        alive_size += s;
        allocated_size += s;
        last_pointer = last_alloc_pointer = p;
        last_size = last_alloc_size = s;
        last_align = last_alloc_align = a;
    }

    void count_dealloc(void* p, size_t s, size_t a) {
        --alive;
        ++dealloc_count;
        alive_size -= s;
        deallocated_size += s;
        last_pointer = last_dealloc_pointer = p;
        last_size = last_dealloc_size = s;
        last_align = last_dealloc_align = a;
    }

    template<class... Args, class Alloc, class Tp>
    void count_construct(Alloc const&, Tp* p) {
        ++construct_called;
        last_construct_pointer = p;
        last_construct_alloc = &make_type_id<Alloc>();
        last_construct_type = &make_type_id<Tp>();
        last_construct_args = &make_argument_id<Args...>();
    }

    template<class Alloc, class Tp>
    void count_destroy(Alloc const&, Tp* p) {
        ++destroy_called;
        last_destroy_alloc = &make_type_id<Alloc>();
        last_destroy_type = &make_type_id<Tp>();
        last_destroy_pointer = p;
    }

    void reset() { std::memset(this, 0, sizeof(*this)); }
    void reset_construct_destroy() {
        construct_called = 0;
        last_construct_pointer = nullptr;
        last_construct_alloc = last_construct_args = last_construct_type = nullptr;
        destroy_called = 0;
        last_destroy_alloc = nullptr;
        last_destroy_pointer = nullptr;
    }

public:
    bool check_alloc(void* p, size_t s, size_t a) const {
        return p == last_alloc_pointer &&
               s == last_alloc_size &&
               a == last_alloc_align;
    }

    bool check_alloc(void* p, size_t s) const {
        return p == last_alloc_pointer &&
               s == last_alloc_size;
    }

    bool check_alloc_at_least(void* p, size_t s, size_t a) const {
        return p == last_alloc_pointer &&
               s <= last_alloc_size &&
               a <= last_alloc_align;
    }

    bool check_alloc_at_least(void* p, size_t s) const {
        return p == last_alloc_pointer &&
               s <= last_alloc_size;
    }

    bool check_dealloc(void* p, size_t s, size_t a) const {
        return p == last_dealloc_pointer &&
               s == last_dealloc_size &&
               a == last_dealloc_align;
    }

    bool check_dealloc(void* p, size_t s) const {
        return p == last_dealloc_pointer &&
               s == last_dealloc_size;
    }

    bool check_dealloc_matches_alloc() const {
        return last_dealloc_pointer == last_alloc_pointer &&
               last_dealloc_size == last_alloc_size &&
               last_dealloc_align == last_alloc_align;
    }

    template<class... Args, class Alloc, class Tp>
    bool check_cnstruct(Alloc const&, Tp* p) const {
        auto expectAlloc = &make_type_id<Alloc>();
        auto expectTp = &make_type_id<Tp>();
        auto expectArgs = &make_argument_id<Args...>();
        return last_construct_pointer == p &&
               COMPARE_TYPEID(last_construct_alloc, expectAlloc) &&
               COMPARE_TYPEID(last_construct_type, expectTp) &&
               COMPARE_TYPEID(last_construct_args, expectArgs);
    }

    template<class Alloc, class Tp>
    bool check_destroy(Alloc const&, Tp* p) const {
        return last_destroy_pointer == p &&
               last_destroy_alloc == &make_type_id<Alloc>() &&
               last_destroy_type == &make_type_id<Tp>();
    }

    bool check_destroy_matches_construct() const {
        return last_destroy_pointer == last_construct_pointer &&
               last_destroy_type == last_construct_type;
    }

    void count_is_equal() {
        ++is_equal_count;
    }

    bool check_is_equal_called_eq(int n) const {
        return is_equal_count == n;
    }

private:
    DISALLOW_COPY(alloc_controller_t);
};

template<class T, size_t ID>
class counting_allocator_t {
public:
    typedef T value_type;
    typedef T* pointer;

    template<class U>
    struct rebind { using other = counting_allocator_t<U, ID>; };

    counting_allocator_t() = delete;
    explicit counting_allocator_t(alloc_controller_t& PP)
        : P(&PP) {}

    counting_allocator_t(counting_allocator_t const& other)
        : P(other.P) {
        P->copy_constructed += 1;
    }

    counting_allocator_t(counting_allocator_t&& other)
        : P(other.P) {
        P->move_constructed += 1;
    }

    template<class U>
    counting_allocator_t(counting_allocator_t<U, ID> const& other) TEST_NOEXCEPT : P(other.P) {
        P->copy_constructed += 1;
    }

    template<class U>
    counting_allocator_t(counting_allocator_t<U, ID>&& other) TEST_NOEXCEPT : P(other.P) {
        P->move_constructed += 1;
    }

    T* allocate(std::size_t n) {
        void* ret = ::operator new(n * sizeof(T));
        P->count_alloc(ret, n * sizeof(T), alignof(T));
        return static_cast<T*>(ret);
    }

    void deallocate(T* p, std::size_t n) {
        void* vp = static_cast<void*>(p);
        P->count_dealloc(vp, n * sizeof(T), alignof(T));
        ::operator delete(vp);
    }

    template<class U, class... Args>
    void construct(U* p, Args&&... args) {
        ::new ((void*) p) U(std::forward<Args>(args)...);
        P->count_construct<Args&&...>(*this, p);
    }

    template<class U>
    void destroy(U* p) {
        p->~U();
        P->count_destroy(*this, p);
    }

    alloc_controller_t& get_controller() const { return *P; }

private:
    template<class Tp, size_t XID>
    friend class counting_allocator_t;
    alloc_controller_t* P;
};

template<size_t ID>
class counting_allocator_t<void, ID> {
public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;

    template<class U>
    struct rebind { using other = counting_allocator_t<U, ID>; };

    counting_allocator_t() = delete;
    explicit counting_allocator_t(alloc_controller_t& PP)
        : P(&PP) {}

    counting_allocator_t(counting_allocator_t const& other)
        : P(other.P) {
        P->copy_constructed += 1;
    }

    counting_allocator_t(counting_allocator_t&& other)
        : P(other.P) {
        P->move_constructed += 1;
    }

    template<class U>
    counting_allocator_t(counting_allocator_t<U, ID> const& other) TEST_NOEXCEPT : P(other.P) {
        P->copy_constructed += 1;
    }

    template<class U>
    counting_allocator_t(counting_allocator_t<U, ID>&& other) TEST_NOEXCEPT : P(other.P) {
        P->move_constructed += 1;
    }

    void construct(...) = delete;
    void destroy(void*) = delete;

    alloc_controller_t& get_controller() const { return *P; }

private:
    template<class Tp, size_t>
    friend class counting_allocator_t;
    alloc_controller_t* P;
};

template<class T, class U, size_t ID>
inline bool operator==(counting_allocator_t<T, ID> const& x,
                       counting_allocator_t<U, ID> const& y) {
    return &x.get_controller() == &y.get_controller();
}

template<class T, class U, size_t ID>
inline bool operator!=(counting_allocator_t<T, ID> const& x,
                       counting_allocator_t<U, ID> const& y) {
    return !(x == y);
}

template<class T>
class null_allocator_t {
public:
    typedef T value_type;
    typedef T* pointer;
    null_allocator_t() = delete;
    explicit null_allocator_t(alloc_controller_t& PP)
        : P(&PP) {}

    null_allocator_t(null_allocator_t const& other)
        : P(other.P) {
        P->copy_constructed += 1;
    }

    null_allocator_t(null_allocator_t&& other)
        : P(other.P) {
        P->move_constructed += 1;
    }

    template<class U>
    null_allocator_t(null_allocator_t<U> const& other) TEST_NOEXCEPT : P(other.P) {
        P->copy_constructed += 1;
    }

    template<class U>
    null_allocator_t(null_allocator_t<U>&& other) TEST_NOEXCEPT : P(other.P) {
        P->move_constructed += 1;
    }

    T* allocate(std::size_t n) {
        P->count_alloc(nullptr, n * sizeof(T), alignof(T));
        return nullptr;
    }

    void deallocate(T* p, std::size_t n) {
        void* vp = static_cast<void*>(p);
        P->count_dealloc(vp, n * sizeof(T), alignof(T));
    }

    alloc_controller_t& get_controller() const { return *P; }

private:
    template<class Tp>
    friend class null_allocator_t;
    alloc_controller_t* P;
};

template<class T, class U>
inline bool operator==(null_allocator_t<T> const& x,
                       null_allocator_t<U> const& y) {
    return &x.get_controller() == &y.get_controller();
}

template<class T, class U>
inline bool operator!=(null_allocator_t<T> const& x,
                       null_allocator_t<U> const& y) {
    return !(x == y);
}
