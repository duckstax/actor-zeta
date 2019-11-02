#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message_header.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>

namespace actor_zeta { namespace actor {
        actor::~actor() {}

        actor_address actor::address() const noexcept {
            return ptr_->address();
        };

        detail::string_view actor::name() const {
            return ptr_->name();
        }

        void actor::swap(actor &other) noexcept {
            using std::swap;
            ptr_.swap(other.ptr_);
        }
}}
