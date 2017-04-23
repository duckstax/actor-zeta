#ifndef SHARED_GROUP_HPP
#define SHARED_GROUP_HPP

#include <unordered_map>

#include "actor-zeta/actor/actor.hpp"
#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace environment {
///
/// @brief Group realisation with common resource
///
        class shared_group {
        public:
            shared_group() = default;

            shared_group(const shared_group &) = delete;

            shared_group(shared_group &&) = default;

            shared_group &operator=(const shared_group &) = delete;

            shared_group &operator=(shared_group &&) = default;

            ~shared_group() = default;

            void add(actor::abstract_actor *);

            void send_current(const std::string &, messaging::message *);

            void send_all(messaging::message *);
        private:
            std::unordered_map<std::string, actor::actor> group_;
        };
    }
}
#endif //SHARED_GROUP_HPP
