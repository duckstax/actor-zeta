#ifndef ABSTRACT_ACTOR_HPP
#define ABSTRACT_ACTOR_HPP

#include <string>

#include "actor-zeta/ref_counted.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace actor {
        class abstract_actor : public ref_counted {
        public:
            const std::string &type() const;

            virtual bool send(messaging::message *) = 0;

            virtual bool send(messaging::message *, executor::execution_device *) = 0;

            virtual ~abstract_actor() {}

            actor_address address() const noexcept;

        protected:
            environment::environment *env() const;

            abstract_actor(environment::environment *, const std::string &);

        private:
            abstract_actor() = delete;

            abstract_actor(const abstract_actor &) = delete;

            abstract_actor &operator=(const abstract_actor &) = delete;

            const std::string type_;

            environment::environment *env_;
        };
    }
}
#endif //ABSTRACT_ACTOR_HPP
