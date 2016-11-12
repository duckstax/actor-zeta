#include "actor-zeta/actor/broker.hpp"
#include "actor-zeta/standard_handlers/write.hpp"


namespace actor_zeta {
    namespace network {

        broker::broker(environment::environment *env,const std::string &name,shared_multiplexer_ptr m_ptr )
                : scheduled_actor(env, name),multiplexer_(std::move(m_ptr)) {
            initialize();
        }

        void broker::initialize() {
            actor::local_actor::initialize();
            attach(new write(multiplexer_));
        }
    }
}
