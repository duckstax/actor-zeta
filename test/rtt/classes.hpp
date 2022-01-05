#pragma once

#include <actor-zeta/detail/any.hpp>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

using actor_zeta::detail::any;
using actor_zeta::detail::any_cast;
using actor_zeta::detail::make_any;

struct X {
    int a = 0;
    std::vector<int> b = std::vector<int>{0};
    X() = default;
    X(X&) = default;
    X(const X&) = default;
    X(X&&) = default;
    ~X() = default;
    X(int a_, std::vector<int> b_)
        : a(a_)
        , b(std::move(b_)) {}
};

struct dummy {
    dummy()
        : alive(true) {
        ++instances_count;
    }

    dummy(const dummy&)
        : alive(true) {
        ++instances_count;
    }

    dummy(dummy&&)
        : alive(true) {
        ++instances_count;
    }

    ~dummy() noexcept(false) {
        if (alive) {
            alive = false;
        } else {
            //throw std::runtime_error(u8"Double destruction!");
        }
        --instances_count;
    }

    bool alive;
    static int instances_count;
};

int dummy::instances_count = 0;

#ifndef __EXCEPTIONS_DISABLE__

struct kamikaze {
    kamikaze() {
        ++instances_count;
    }

    kamikaze(kamikaze&) = default;
    kamikaze(const kamikaze&) = default;

    kamikaze(kamikaze&&) {
        if (instances_count > 4) {
            throw std::runtime_error(u8"Привет!");
        }
        ++instances_count;
    }

    ~kamikaze() {
        --instances_count;
    }

    static int instances_count;
};

int kamikaze::instances_count = 0;

struct throw_on_move {
    throw_on_move() = default;
    throw_on_move(const throw_on_move&) = default;
    throw_on_move& operator=(const throw_on_move&) = default;
    throw_on_move(throw_on_move&&) {
        throw std::runtime_error(u8"Пока!");
    }
    throw_on_move& operator=(throw_on_move&&) = default;
    ~throw_on_move() = default;
};

#endif

struct move_constructor_counter {
    explicit move_constructor_counter(std::size_t& move_count)
        : move_count(move_count) {
    }

    move_constructor_counter(move_constructor_counter&& that)
        : move_count(that.move_count) {
        ++move_count;
    }

    std::size_t& move_count;
};

struct destructor_counter {
    explicit destructor_counter(std::size_t& destruct_count)
        : destruct_count(destruct_count) {
    }

    ~destructor_counter() {
        ++destruct_count;
    }

    std::size_t& destruct_count;
};

template<typename... Ts>
void ignore_unused(Ts const&...) {}

template<typename... Ts>
void ignore_unused() {}
