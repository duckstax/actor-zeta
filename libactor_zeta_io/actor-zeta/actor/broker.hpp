#ifndef BROKER_HPP
#define BROKER_HPP

#include <unordered_map>

#include "actor-zeta/actor/scheduled_actor.hpp"
#include "actor-zeta/actor/basic_actor.hpp"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/network/multiplexer.hpp"

namespace actor_zeta {
    namespace network {
///
/// @brief
///
        class broker : public actor::basic_actor<actor::scheduled_actor,messaging::blocking_mail_queue,behavior::behavior> {
        public:
            broker(environment::environment * env, const std::string & name, shared_multiplexer_ptr ptr)
                    : actor::basic_actor<actor::scheduled_actor,messaging::blocking_mail_queue,behavior::behavior>(env, name),
                      multiplexer_(std::move(ptr)) {
                initialize();
            }

            virtual ~broker() = default;

        protected:
            void initialize() override;

            std::shared_ptr<multiplexer> multiplexer_;
        };
    }
}
#endif //ABSTRACT_BROKER_HPP
