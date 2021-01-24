// clang-format off
#include <address_t.hpp>
#include <message.hpp>
#include <abstract_supervisor.hpp>
// clang-format on

#include "actor-zeta/supervisor.hpp"



namespace actor_zeta {

    address_t supervisor::address() const noexcept {
        return address_t(ptr_.get());
    }

    detail::string_view supervisor::name() const {
        return ptr_->name();
    }

    void supervisor::swap(supervisor& other) noexcept {
        using std::swap;
        ptr_.swap(other.ptr_);
    }

    supervisor::supervisor(std::nullptr_t)
        : ptr_(nullptr) {}

    supervisor& supervisor::operator=(std::nullptr_t) {
        ptr_.reset();
        return *this;
    }

    supervisor::~supervisor() = default;
}