#ifndef BLOCKING_ACTOR_HPP
#define BLOCKING_ACTOR_HPP

#include <mutex>
#include <condition_variable>
#include "actor-zeta/forwards.hpp"
#include "local_actor.hpp"

namespace actor_zeta {
    namespace actor {
///
/// @brief Specialization of actor with blocking mode
///
        class blocking_actor  : public local_actor , executor::executable {
        public:
            blocking_actor(environment::environment *,mailbox_type* ,behavior::abstract_behavior*, const std::string &);
            executor::executable_result run(executor::execution_device *, size_t) override final;
            void launch(executor::execution_device *,bool) override final ;
            virtual ~blocking_actor(){}

        private:
            std::mutex mtx;
            std::condition_variable condition;
        };
    }
}
#endif //BLOCKING_ACTOR_HPP
