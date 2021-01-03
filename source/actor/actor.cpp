
// clang-format off
#include <actor-zeta/base/address_type.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/abstract_actor.hpp>
// clang-format on

namespace actor_zeta { namespace base {
        actor::~actor() {}

        address_type actor::address() const noexcept {
            return ptr_->get()->address();
        }

        detail::string_view actor::name() const {
            return ptr_->get()->name();
        }

        void actor::swap(actor &other) noexcept {
            using std::swap;
            ptr_.swap(other.ptr_);
        }

        actor::actor(std::nullptr_t) : ptr_(nullptr) {}

        actor &actor::operator=(std::nullptr_t) {
            ptr_.reset();
            return *this;
        }
}}
