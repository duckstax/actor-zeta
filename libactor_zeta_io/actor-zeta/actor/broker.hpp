#ifndef BROKER_HPP
#define BROKER_HPP

#include <memory>
#include "actor-zeta/actor/basic_actor.hpp"
#include "actor-zeta/network/multiplexer.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief
///

        class broker : public basic_scheduled_actor  {
        public:
            broker(environment::abstract_environment * env, const std::string & name, network::shared_multiplexer_ptr multiplexer)
                    : basic_scheduled_actor(env, name),
                      multiplexer_(std::move(multiplexer)) {
                initialize();
            }

            virtual ~broker() override = default;

        protected:
            void initialize() override;

            network::shared_multiplexer_ptr multiplexer_;
        };
    }
}
#endif //ABSTRACT_BROKER_HPP
