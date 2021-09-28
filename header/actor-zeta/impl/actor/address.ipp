#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/communication_module.hpp>
#include <memory>

namespace {
    constexpr static actor_zeta::detail::string_view non_type("non-type");
}

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

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

    void address_t::enqueue(message_ptr msg) noexcept {
        ptr_->enqueue(std::move(msg));
    }

    auto address_t::type() const -> detail::string_view {
        return ptr_->type();
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

    void* address_t::get() const {
        return ptr_;
    }

    address_t::~address_t() noexcept {
        ptr_ = nullptr;
    }

}} // namespace actor_zeta::base
