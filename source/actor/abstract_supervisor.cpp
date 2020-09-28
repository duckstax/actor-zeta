// clang-format off
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/base/abstract_supervisor.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    abstract_supervisor::abstract_supervisor(detail::string_view name)
        : communication_module(name, abstract::supervisor) {}

    abstract_supervisor::~abstract_supervisor() {}

    auto abstract_supervisor::current_message() -> messaging::message& {
        return current_message_;
    }

    auto abstract_supervisor::set_current_message(messaging::message msg) -> void {
        current_message_ = std::move(msg);
    }

    actor_address supervisor::address() const noexcept {
        return ptr_->address();
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

    supervisor::~supervisor() {
    }

}} // namespace actor_zeta::base