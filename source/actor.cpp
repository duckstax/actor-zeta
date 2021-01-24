
// clang-format off
#include <address_t.hpp>
#include <message.hpp>
#include <actor.hpp>
#include <abstract_actor.hpp>
// clang-format on

namespace actor_zeta {

        actor::actor(std::nullptr_t) : ptr_(nullptr) {}

        actor& actor::operator=(std::nullptr_t) {
            ptr_.reset();
            return *this;
        }

        void actor::swap(actor& other) noexcept {
            ptr_.swap(other.ptr_);
        }

        address_t actor::address() const noexcept {
            return address_t{ptr_.get()};
        }
}