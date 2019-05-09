#include <actor-zeta/actor/abstract_action.hpp>


namespace actor_zeta { namespace actor {
    abstract_action::~abstract_action() = default;

    auto abstract_action::name() const -> const type_action & {
      return name_;
    }

}// namespace actor_zeta
} // namespace behavior
