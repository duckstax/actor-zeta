#ifndef ABSTRACT_ACTOR_HPP
#define ABSTRACT_ACTOR_HPP

#include <string>
#include <actor-zeta/environment/environment.hpp>
#include "actor-zeta/ref_counted.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief Abstract concept of an actor
///
        class abstract_actor : public ref_counted {
        public:
            const std::string &type() const;

            virtual bool send(messaging::message&&) = 0;

            virtual bool send(messaging::message&&, executor::execution_device *) = 0;

            virtual ~abstract_actor() {}

            actor_address address() const noexcept;

        protected:
            environment::environment& env() ;

            abstract_actor(environment::abstract_environment *, const std::string &);

        private:
            abstract_actor() = delete;

            abstract_actor(const abstract_actor &) = delete;

            abstract_actor &operator=(const abstract_actor &) = delete;

            const std::string name_;

            environment::environment env_;
        };
    }
}
#endif //ABSTRACT_ACTOR_HPP
