#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/environment/group.hpp"
#include <algorithm>
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/actor/abstract_actor.hpp"
#include "actor-zeta/actor/actor.hpp"

namespace actor_zeta {
    namespace environment {
        void group::send(messaging::message *msg) {
            unique_actors[entry_point]->send(msg);
        }

        void group::send_all(messaging::message *msg) {
            for (auto &i:unique_actors)
                i.second->send(msg);
        }

        std::string group::name_entry_point() const {
            return entry_point;
        }

        actor::actor_address group::address_entry_point() const {
            return unique_actors.at(entry_point).address();
        }

        void group::sync(std::initializer_list<std::string> list_names) {
            entry_point = *(list_names.begin());
            std::vector<std::string> tmp(list_names);
            std::reverse(tmp.begin(), tmp.end());

            for (auto i = tmp.begin(); i != tmp.end(); ++i) {
                auto j = i;
                ++j;
                if (j == tmp.end()) {
                    return;
                }
                unique_actors[*(j)]->send(
                        messaging::make_message(
                                "sync_contacts",
                                unique_actors[*(i)].address()
                        )
                );
            }
        }

        void group::add_shared_address(actor::actor_address address) {
            for (auto &i:unique_actors)
                i.second->send(
                        messaging::make_message(
                                "sync_contacts",
                                address
                        )
                );
        }

        void group::add(actor::actor &&a) {
            unique_actors.emplace(a.type(), std::move(a));
        }

        void group::sync() {
            if (unique_actors.size() == 1) {
                entry_point = (*unique_actors.begin()).first;
            }

        }

        const std::string &group::name() const {
            return name_;
        }

        void group::add(const std::string &root_name, actor::abstract_actor *actor) {
            actor_zeta::actor::actor_address address = actor->address();
            unique_actors.emplace(actor->type(), actor::actor(actor));
            unique_actors[root_name]->send(
                    messaging::make_message(
                            "sync_contacts",
                            address
                    )
            );

        }

        void group::add(actor::abstract_actor *actor)  {
            unique_actors.emplace(actor->type(), actor::actor(actor));
        }

        group::group(const std::string &name, actor::abstract_actor *actor) :name_(name) {
            std::string entry_address = actor->type();
            unique_actors.emplace(actor->type(),actor::actor(actor));
            entry_point = entry_address;
        }
    }
}