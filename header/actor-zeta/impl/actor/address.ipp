#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <header/actor-zeta/mailbox/message.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <actor-zeta/base/address.hpp>
#include <memory>

namespace actor_zeta { namespace base {

    address_t::address_t() noexcept
        : ptr_(nullptr) {
    }

    address_t::address_t(actor_abstract* ptr)
        : ptr_(ptr) {
        assert(ptr != nullptr);
    }

    address_t::address_t(supervisor_abstract* ptr)
        : ptr_(ptr) {
        assert(ptr != nullptr);
    }

    bool address_t::operator!() const noexcept {
        return !(static_cast<bool>(ptr_));
    }

    address_t::operator bool() const noexcept {
        return static_cast<bool>(ptr_);
    }

    address_t::address_t(address_t&& other) noexcept {
        swap(other);
    }

    address_t::address_t(const address_t& other) {
        if (this != &other) {
            ptr_ = other.ptr_;
        }
    }

    address_t& address_t::operator=(address_t&& other) noexcept {
        if (this != &other) {
            swap(other);
        }
        return *this;
    }

    address_t& address_t::operator=(const address_t& other) {
        if (this != &other) {
            address_t tmp(other);
            swap(tmp);
        }
        return *this;
    }

    void address_t::swap(address_t& other) {
        using std::swap;
        std::swap(ptr_, other.ptr_);
    }

    actor_abstract* address_t::get() const {
        return ptr_;
    }

    address_t::~address_t() noexcept {
        ptr_ = nullptr;
    }

    auto address_t::empty_address() -> address_t {
        static address_t tmp;
        return tmp;
    }

    bool address_t::operator==(const address_t& rhs) noexcept {
        return  ptr_ == rhs.ptr_;
    }

    bool operator==(const address_t& lhs, const address_t& rhs) noexcept {
        return lhs == rhs;
    }

}} // namespace actor_zeta::base
