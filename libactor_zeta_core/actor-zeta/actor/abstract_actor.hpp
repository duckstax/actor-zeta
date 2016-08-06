#ifndef ABSTRACT_ACTOR_HPP
#define ABSTRACT_ACTOR_HPP

#include <mutex>
#include <condition_variable>
#include <string>

#include "actor-zeta/ref_counted.hpp"
#include "actor.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace actor {
        class abstract_actor : public ref_counted {
        public:
            const std::string& type() const;

            virtual bool async_send(messaging::message &&) = 0;

            virtual bool async_send(messaging::message &&, executor::execution_device *) = 0;

            virtual ~abstract_actor() {};

            actor_address address() const noexcept;

            bool remote() const noexcept;

            void remote(bool) noexcept;

            bool blocked() const noexcept;

            void blocked(bool)noexcept;

            bool master() const noexcept;

            void master(bool)noexcept;

        protected:
            abstract_actor(environment::environment &, const std::string &);

            environment::environment &env;
        private:
            abstract_actor() = delete;

            abstract_actor(const abstract_actor &) = delete;

            abstract_actor &operator=(const abstract_actor &) = delete;

            const std::string type_;
            bool remote_;
            bool blocked_;
            bool master_;
        };
    }
}
#endif //ABSTRACT_ACTOR_HPP
