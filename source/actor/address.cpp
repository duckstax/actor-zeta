// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <memory>

namespace {
    constexpr static actor_zeta::detail::string_view non_type("non-type");
}

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

    address_t::address_t(actor_abstract* ptr)
        : ptr_(ptr) {
    }

    address_t::address_t(supervisor_abstract* ptr)
        : ptr_(ptr) {
    }

    address_t::~address_t() {
        ptr_ = nullptr;
    }

    bool address_t::operator!() const noexcept {
        return !(static_cast<bool>(ptr_) );
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

    address_t::address_t() noexcept
        : ptr_() {
    }

    address_t::address_t(address_t&& other) noexcept
            : address_t() {
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

    address_t::address_t(std::nullptr_t) noexcept
            : address_t() {}

     void address_t::swap(address_t& other) {
            using std::swap;
            std::swap(ptr_, other.ptr_);
        }

    void* address_t::get() const {
        return ptr_;
    }


}} // namespace actor_zeta::base
