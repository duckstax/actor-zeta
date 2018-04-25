#include <actor-zeta/behavior/abstract_action.hpp>


namespace actor_zeta { namespace behavior{
    abstract_action::~abstract_action() = default;

    auto actor_zeta::behavior::abstract_action::name() const -> const type_action & {
      return name_;
    }

}// namespace actor_zeta
} // namespace behavior
