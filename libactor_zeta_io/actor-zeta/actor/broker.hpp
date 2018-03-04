#ifndef BROKER_HPP
#define BROKER_HPP

#include <unordered_map>
#include <actor-zeta/messaging/blocking_mail_queue.hpp>
#include "actor-zeta/actor/scheduled_actor.hpp"
#include "actor-zeta/actor/basic_actor.hpp"
#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/network/multiplexer.hpp"

namespace actor_zeta {
    namespace network {
///
/// @brief
///
        using basic_scheduled_actor = actor::basic_actor<messaging::blocking_mail_queue,behavior::behavior>;

        class broker : public basic_scheduled_actor  {
        public:
            broker(environment::abstract_environment * env, const std::string & name, shared_multiplexer_ptr ptr)
                    : basic_scheduled_actor(env, name),
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
