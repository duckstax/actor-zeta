#ifndef BROKER_HPP
#define BROKER_HPP

#include <memory>
#include "actor-zeta/actor/basic_actor.hpp"
#include <actor-zeta-io/network/multiplexer.hpp>

namespace actor_zeta {
    namespace actor {
///
/// @brief
///

        class broker : public basic_async_actor  {
        public:
            broker(environment::abstract_environment * env, const std::string & name, network::multiplexer* multiplexer)
                    : basic_async_actor(env, name),
                      multiplexer_(multiplexer) {
            }

            virtual ~broker() override = default;

        protected:
            void initialize() override;

            intrusive_ptr<network::multiplexer> multiplexer_;
        };
    }
}
#endif //ABSTRACT_BROKER_HPP
