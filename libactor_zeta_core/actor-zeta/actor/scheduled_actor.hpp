#ifndef SCHEDULED_ACTOR_HPP
#define SCHEDULED_ACTOR_HPP

#include "actor-zeta/executor/execution_device.hpp"
#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief Specialization of actor with scheduling functionality
///
        class scheduled_actor : public local_actor, public executor::executable {
        public:
            bool send(messaging::message *) override final;

            bool send(messaging::message *, executor::execution_device *) override final;

            void launch(executor::execution_device *, bool) override final;

            executor::executable::executable_result run(executor::execution_device *, size_t max_throughput) override final;

        protected:
            scheduled_actor(environment::environment *, const std::string &);

            void attach_to_scheduler() override final;

            void detach_from_scheduler() override final;
        };
    }
}
#endif //SCHEDULED_ACTOR_HPP
