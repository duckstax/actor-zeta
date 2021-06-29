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
        : sub_type_(sub_type_t::actor)
        , ptr_(ptr) {
    }

    address_t::address_t(supervisor_abstract* ptr)
        : sub_type_(sub_type_t::supervisor)
        , ptr_(ptr) {
    }

    address_t::~address_t() {
        ptr_.destroy(sub_type_);
        sub_type_ = sub_type_t::none;
    }
    bool address_t::operator!() const noexcept {
        return !(static_cast<bool>(ptr_.actor_) || static_cast<bool>(ptr_.supervisor_));
    }

    address_t::operator bool() const noexcept {
        return static_cast<bool>(ptr_.actor_) || static_cast<bool>(ptr_.supervisor_);
    }

    void address_t::enqueue(message_ptr msg) noexcept {
        switch (sub_type_) {
            case sub_type_t::none:
                 std::abort();
            case sub_type_t::actor:
                ptr_.actor_->enqueue(std::move(msg));
                break;
            case sub_type_t::supervisor:
                ptr_.supervisor_->enqueue(std::move(msg));
                break;
        }
    }

    auto address_t::type() const -> detail::string_view {
        switch (sub_type_) {
            case sub_type_t::none:
                std::abort();
                //return non_type ;
            case sub_type_t::actor:
                return ptr_.actor_->type();
            case sub_type_t::supervisor:
                return ptr_.supervisor_->type();
            default:
                return non_type;
        }
    }

    address_t::address_t() noexcept
        : sub_type_(sub_type_t::none)
        , ptr_() {
    }

    address_t::address_t(address_t&& other) noexcept
            : address_t() {
            swap(other);
        }

    address_t::address_t(const address_t& other) {
            if (this != &other) {
                ptr_ = other.ptr_;
                sub_type_ = other.sub_type_;
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
            std::swap(sub_type_, other.sub_type_);
        }


}} // namespace actor_zeta::base
