#ifndef BLOCKING_ACTOR_HPP
#define BLOCKING_ACTOR_HPP

#include <mutex>

#include "actor-zeta/forwards.hpp"
#include "local_actor.hpp"

namespace actor_zeta {
    namespace actor {
        class blocking_actor : public local_actor , executor::executable {
        public:
            blocking_actor(environment::environment *, const std::string &);
            virtual void act();
            executor::executable::executable_result run(executor::execution_device *, size_t) override final;
            void launch(executor::execution_device *,bool) override final ;
            virtual ~blocking_actor(){}

        private:
            std::mutex mtx;
            std::condition_variable condition;
        };
    }
}
#endif //BLOCKING_ACTOR_HPP
