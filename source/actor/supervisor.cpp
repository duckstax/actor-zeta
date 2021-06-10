// clang-format off
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/supervisor.hpp>
// clang-format on

#include <actor-zeta/base/supervisor_abstract.hpp>

namespace actor_zeta { namespace base {

    supervisor::~supervisor() {}

    actor_address supervisor::address() const noexcept {
        return ptr_->address();
    }

    detail::string_view supervisor::type() const {
        return ptr_->type();
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

}} // namespace actor_zeta::base