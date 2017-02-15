#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/environment/group.hpp"
#include <algorithm>
#include <iostream>
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/actor/actor.hpp"

namespace actor_zeta {
    namespace environment {
        void group::send(messaging::message *msg) {
            unique_actors[name_entry_point]->send(msg);
        }

        void group::send_all(messaging::message *msg) {
            std::unique_ptr<messaging::message>unique_ptr_msg(msg);
            for (auto &i:unique_actors) {
                i.second->send(unique_ptr_msg->clone());
            }
        }

        actor::actor_address group::entry_point() const {
            return unique_actors.at(name_entry_point).address();
        }

        void group::add(actor::actor &&a) {
            unique_actors.emplace(a.type(), std::move(a));
        }

        const std::string &group::name() const {
            return name_;
        }

        void group::add(const std::string &root_name, actor::abstract_actor *actor) {
            actor_zeta::actor::actor_address address = actor->address();
            unique_actors.emplace(actor->type(), actor::actor(actor));
            send_current(
                    root_name,
                    messaging::make_message(
                            "sync_contacts",
                            address
                    )
            );
        }

        void group::add(actor::abstract_actor *actor) {
            unique_actors.emplace(actor->type(), actor::actor(actor));
        }

        group::group(const std::string &name, actor::abstract_actor *actor) : name_(name) {
            std::string entry_address = actor->type();
            unique_actors.emplace(actor->type(), actor::actor(actor));
            name_entry_point = entry_address;
        }

        void group::add_shared(actor::abstract_actor *actor) {
            actor::actor_address address = actor->address();
            shared_group_.add(actor);
            send_all(
                    messaging::make_message(
                            "sync_contacts",
                            address
                    )
            );
        }

        void group::send_current(const std::string &name, messaging::message *msg) {
            unique_actors[name]->send(msg);
        }
    }
}