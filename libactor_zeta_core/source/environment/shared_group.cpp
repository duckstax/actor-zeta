#include "actor-zeta/environment/shared_group.hpp"

namespace actor_zeta {
    namespace environment {
        void shared_group::add(actor::abstract_actor *a) {
            group_.emplace(a->type(), std::move(actor::actor(a)));
        }

        void shared_group::send_current(const std::string &name, messaging::message *msg) {
            group_.at(name)->send(msg);
        }

        void shared_group::send_all(messaging::message *msg) {
            std::unique_ptr<messaging::message> unique_ptr_msg(msg);
            for (auto &i:group_) {
                i.second->send(unique_ptr_msg->clone());
            }
        }
    }
}