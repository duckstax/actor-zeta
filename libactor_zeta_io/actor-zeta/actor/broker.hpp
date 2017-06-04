#ifndef BROKER_HPP
#define BROKER_HPP

#include <unordered_map>

#include "actor-zeta/actor/scheduled_actor.hpp"
#include "actor-zeta/network/multiplexer.hpp"

namespace actor_zeta {
    namespace network {
///
/// @brief
///
        class broker : public actor_zeta::actor::scheduled_actor {
        public:
            broker(environment::environment *, const std::string &, shared_multiplexer_ptr);

            virtual ~broker() = default;

        protected:
            void initialize() override;

            std::shared_ptr<multiplexer> multiplexer_;
        };
    }
}
#endif //ABSTRACT_BROKER_HPP
