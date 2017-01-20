#ifndef ABSTRACT_ACTION_HPP
#define ABSTRACT_ACTION_HPP

#include "actor-zeta/forwards.hpp"
#include "type_action.hpp"

namespace actor_zeta {
    namespace behavior {
        class abstract_action {
        private:
            const type_action name_;
        public:
            template<std::size_t N>
            abstract_action(const char(&aStr)[N]) : name_(aStr) {}

            virtual response * operator()(request *) = 0;

            auto name() const -> const type_action & {
                return name_;
            }

            virtual ~abstract_action() = default;
        };
    }
}
#endif
