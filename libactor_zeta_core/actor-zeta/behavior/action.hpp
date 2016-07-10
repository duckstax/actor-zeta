#ifndef ACTION_HPP
#define ACTION_HPP

#include <memory>

#include "abstract_action.hpp"

namespace actor_zeta {
    namespace behavior {
        class action {
        public:
            action() = default;

            action(const action &) = delete;

            action &operator=(const action &)= delete;

            action(action &&) = default;

            action &operator=(action &&)= default;

            ~action() = default;

            action(abstract_action *aa) : action_impl_ptr(aa) {}

            void operator()(messaging::message &&msg) {
                action_impl_ptr->operator()(std::move(msg));
            }

        private:
            std::unique_ptr<abstract_action> action_impl_ptr;
        };
    }
}
#endif //ACTION_HPP
