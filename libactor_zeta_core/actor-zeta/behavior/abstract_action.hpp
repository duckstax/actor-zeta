#ifndef ABSTRACT_ACTION_HPP
#define ABSTRACT_ACTION_HPP

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/behavior/type_action.hpp>
#include <actor-zeta/behavior/state.hpp>

namespace actor_zeta { namespace behavior {
///
/// @brief Abstract concept of an action
///
        class abstract_action {      
        public:
            virtual ~abstract_action();

            template<std::size_t N>
            abstract_action(const char(&aStr)[N]) : name_(aStr) {}

            virtual void invoke(context &) = 0;

            auto name() const -> const type_action &;

        private:
            const type_action name_;
        };

    } /// namespace behavior
} /// namespace actor_zeta
#endif
