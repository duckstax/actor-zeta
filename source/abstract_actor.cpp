#include <iostream>

// clang-format off
#include <handler.hpp>
#include <address_t.hpp>
#include <message.hpp>
#include <abstract_actor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta {



        abstract_actor::~abstract_actor() {}

        abstract_actor::abstract_actor(detail::string_view name): communication_module(name, abstract::actor) {
            // nop
        }

        address_t abstract_actor::address() const noexcept {
            return address_t(this);
        }

    void abstract_actor::enqueue(message msg, executor::execution_device* ptr) {
        enqueue_base(std::move(msg), ptr);
    }

    void abstract_actor::enqueue(message msg) {
        enqueue(std::move(msg), nullptr);
    }

}
