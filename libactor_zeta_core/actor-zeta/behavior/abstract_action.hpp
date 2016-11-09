#ifndef ABSTRACT_ACTION_HPP
#define ABSTRACT_ACTION_HPP

#include <string>
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace behavior {
        class abstract_action {
        private:
            std::string name_;
        public:
            abstract_action(const std::string &name_) : name_(name_) {}

            virtual response *operator()(request *) = 0;

            const std::string &name() const {
                return name_;
            }

            virtual ~abstract_action() = default;
        };
    }
}
#endif
