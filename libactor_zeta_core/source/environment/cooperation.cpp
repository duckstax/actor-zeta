#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/environment/cooperation.hpp"
#include "actor-zeta/environment/group.hpp"
#include "actor-zeta/actor/local_actor.hpp"
#include <algorithm>

namespace actor_zeta {
    namespace environment {
        void cooperation::send(messaging::message *msg) {
            cooperation_groups[entry_point].send(msg);
        }

        void cooperation::add(group &&g) {
            cooperation_groups.emplace(g.name(), std::move(g));
        }

        void cooperation::send_all(messaging::message *msg) {
            std::unique_ptr<messaging::message>unique_ptr_msg(msg);
            for (auto &i:cooperation_groups) {
                i.second.send_all(unique_ptr_msg->clone());
            }
        }

        void cooperation::add_shared(actor::abstract_actor* actor) {
            actor::actor_address address=actor->address();
            shared_group_.add(actor);
            send_all(
                    messaging::make_message(
                            "sync_contacts",
                            address
                    )
            );
        }

        void cooperation::send_current(const std::string &name, messaging::message *message) {
            cooperation_groups[name].send(message);
        }

        actor_zeta::actor::actor_address cooperation::get(const std::string & name) const {
            return actor_zeta::actor::actor_address(cooperation_groups.at(name).entry_point());
        }
    }
}