#pragma once

#include <actor-zeta/detail/any.hpp>
#include <numeric>
#include <string>
#include <vector>

using actor_zeta::detail::any;
using actor_zeta::detail::any_cast;
using actor_zeta::detail::make_any;

constexpr static uint32_t magic_value = 0x01f1cbe8;

struct big_object final {
    int x_;
    bool throw_on_copy_;
    int64_t id_;
    uint32_t magic_value_;
    static int64_t counter_;
    static int64_t constructor_counter_;
    static int64_t destructor_counter_;
    static int64_t default_constructor_counter_;
    static int64_t arg_constructor_counter_;
    static int64_t copy_constructor_counter_;
    static int64_t move_constructor_counter_;
    static int64_t copy_assign_counter_;
    static int64_t move_assign_counter_;
    static int magic_error_counter_;

    explicit big_object(int x = 0, bool bThrowOnCopy = false)
        : x_(x)
        , throw_on_copy_(bThrowOnCopy)
        , magic_value_(magic_value) {
        ++counter_;
        ++constructor_counter_;
        ++default_constructor_counter_;
        id_ = constructor_counter_;
    }

    big_object(int x0, int x1, int x2, bool throw_on_copy = false)
        : x_(x0 + x1 + x2)
        , throw_on_copy_(throw_on_copy)
        , magic_value_(magic_value) {
        ++counter_;
        ++constructor_counter_;
        ++arg_constructor_counter_;
        id_ = constructor_counter_;
    }

    big_object(const big_object& other)
        : x_(other.x_)
        , throw_on_copy_(other.throw_on_copy_)
        , magic_value_(other.magic_value_) {
        ++counter_;
        ++constructor_counter_;
        ++copy_constructor_counter_;
        id_ = constructor_counter_;
    }

    big_object(big_object&& other) ///TODO: noexcept
        : x_(other.x_)
        , throw_on_copy_(other.throw_on_copy_)
        , magic_value_(other.magic_value_) {
        ++counter_;
        ++constructor_counter_;
        ++move_constructor_counter_;
        id_ = constructor_counter_;
        other.x_ = 0;
    }

    big_object& operator=(const big_object& other) {
        ++copy_assign_counter_;

        if (&other != this) {
            x_ = other.x_;
            magic_value_ = other.magic_value_;
            throw_on_copy_ = other.throw_on_copy_;
        }
        return *this;
    }

    big_object& operator=(big_object&& other) {
        ++move_assign_counter_;

        if (&other != this) {
            std::swap(x_, other.x_);
            std::swap(magic_value_, other.magic_value_);
            std::swap(throw_on_copy_, other.throw_on_copy_);
        }
        return *this;
    }

    ~big_object() {
        if (magic_value_ != magic_value) {
            ++magic_error_counter_;
        }
        magic_value_ = 0;
        --counter_;
        ++destructor_counter_;
    }

    static void reset() {
        counter_ = 0;
        constructor_counter_ = 0;
        destructor_counter_ = 0;
        default_constructor_counter_ = 0;
        arg_constructor_counter_ = 0;
        copy_constructor_counter_ = 0;
        move_constructor_counter_ = 0;
        copy_assign_counter_ = 0;
        move_assign_counter_ = 0;
        magic_error_counter_ = 0;
    }

    static bool is_clear() {
        //std::cout << counter_ << constructor_counter_ << destructor_counter_ << magic_error_counter_ << std::endl;
        return (counter_ == 0) && (destructor_counter_ == constructor_counter_) && (magic_error_counter_ == 0);
    }
};

int64_t big_object::counter_ = 0;
int64_t big_object::constructor_counter_ = 0;
int64_t big_object::destructor_counter_ = 0;
int64_t big_object::default_constructor_counter_ = 0;
int64_t big_object::arg_constructor_counter_ = 0;
int64_t big_object::copy_constructor_counter_ = 0;
int64_t big_object::move_constructor_counter_ = 0;
int64_t big_object::copy_assign_counter_ = 0;
int64_t big_object::move_assign_counter_ = 0;
int big_object::magic_error_counter_ = 0;

struct small_object final {
    static int constructor_counter_;

    small_object() noexcept { constructor_counter_++; }
    small_object(const small_object&) noexcept { constructor_counter_++; }
    small_object(small_object&&) noexcept { constructor_counter_++; }
    small_object& operator=(const small_object&) noexcept {
        constructor_counter_++;
        return *this;
    }
    ~small_object() noexcept { constructor_counter_--; }

    static void reset() { constructor_counter_ = 0; }
    static bool is_clear() { return constructor_counter_ == 0; }
};

int small_object::constructor_counter_ = 0;

struct list_of_numbers final {
    list_of_numbers(std::initializer_list<int> numbers)
        : sum(std::accumulate(begin(numbers), end(numbers), 0)) {}

    int sum;
};

template<typename... Ts>
void ignore_unused(Ts const&...) {}

template<typename... Ts>
void ignore_unused() {}
