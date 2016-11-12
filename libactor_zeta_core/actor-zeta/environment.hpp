#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "actor-zeta/environment/group.hpp"
#include "actor-zeta/environment/cooperation.hpp"

// TODO:  environment -> abstract_environment

namespace actor_zeta {
    namespace environment {

        class environment {
        public:
            environment() = delete;

            environment(const environment &) = delete;

            environment &operator=(const environment &) = delete;

            environment(environment &&) = default;

            environment &operator=(environment &&) = default;

            ~environment() = default;

            virtual int start();

            environment(executor::abstract_coordinator *);

            executor::abstract_coordinator& manager_execution_device();

            cooperation& manager_group();

        private:
            cooperation cooperation_;
        protected:
            executor::abstract_coordinator* coordinator_;
        };
    }
}

#endif //ENVIRONMENT_HPP