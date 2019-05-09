#pragma once

#include <memory>
#include "actor-zeta/actor/basic_actor.hpp"
#include "actor-zeta/network/multiplexer.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief
///

        class broker : public basic_async_actor  {
        public:
            template<std::size_t N>
            broker(environment::abstract_environment * env,  const char(&name)[N], network::multiplexer* multiplexer)
                    : basic_async_actor(env, name),
                      multiplexer_(multiplexer) {
            }

            ~broker() override = default;

        protected:
            intrusive_ptr<network::multiplexer> multiplexer_;
        };
    }
}
