#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/environment/group.hpp"
#include <algorithm>

namespace actor_zeta {
    namespace environment {
        void group::async_send(messaging::message &&msg) {
            unique_actors[entry_point]->async_send(std::move(msg));
        }

        void group::async_send_all(messaging::message &&msg) {
            for (auto &i:unique_actors)
                i.second->async_send(std::move(msg));
        }

        std::string group::name_entry_point() const {
            return entry_point;
        }

        actor::actor_address group::address_entry_point() const {
            return actor::actor_address(unique_actors.at(entry_point).address());
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
                unique_actors[*(j)]->async_send(
                        messaging::make_message(
                                std::string("sync_contacts"),
                                unique_actors[*(i)].address()
                        )
                );
            }
        }

        group &group::add_shared_address(actor::actor_address address) {
            for (auto &i:unique_actors)
                i.second->async_send(
                        messaging::make_message(
                                std::string("sync_contacts"),
                                address
                        )
                );
            return *this;
        }

        group &group::add(actor::actor &&a) {
            unique_actors.emplace(a.type(), std::move(a));
            return *this;
        }

        void group::sync() {
            if (unique_actors.size() == 1) {
                entry_point = (*unique_actors.begin()).first;
            }

        }

        const std::string &group::name() const {
            return name_;
        }
    }
}