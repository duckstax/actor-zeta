#ifndef ACTION_HPP
#define ACTION_HPP

#include <memory>

#include "abstract_action.hpp"

namespace actor_zeta {
    namespace behavior {
///
/// @brief Basic action implementation
///
        class action final {
        public:
            action() = default;

            action(const action &) = delete;

            action &operator=(const action &)= delete;

            action(action &&) = default;

            action &operator=(action &&)= default;

            ~action() = default;

            explicit action(abstract_action *);

            response *operator()(request *);

        private:
            std::unique_ptr<abstract_action> action_impl_ptr;
        };
    }
}
#endif //ACTION_HPP
