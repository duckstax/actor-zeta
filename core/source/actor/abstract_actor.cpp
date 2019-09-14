#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>

namespace actor_zeta { namespace actor {

        actor_address abstract_actor::address() const noexcept {
            return actor_address{const_cast<abstract_actor *>(this)};
        }

        abstract_actor::~abstract_actor() {

        }

        auto abstract_actor::type() const -> abstract {
            return type_.type;
        }

        auto abstract_actor::name() const -> detail::string_view {
            return type_.name;
        }

        auto abstract_actor::message_types() const -> std::set<std::string> {
            return std::set<std::string>();
        }

        abstract_actor::abstract_actor(detail::string_view name) {
            type_.name = name;
        }

        void abstract_actor::enqueue(messaging::message msg) {
            enqueue(std::move(msg), nullptr);
        }

}}
