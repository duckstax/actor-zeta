#include "actor-zeta/behavior/behavior.hpp"
#include "actor-zeta/environment/cooperation.hpp"
#include "actor-zeta/environment/group.hpp"
#include "actor-zeta/actor/local_actor.hpp"
#include <algorithm>

namespace actor_zeta {
    namespace environment {
        void cooperation::async_send(messaging::message &&msg) {
            cooperation_groups[entry_point].async_send(std::move(msg));
        }

        void cooperation::sync(std::initializer_list<std::string> list_names) {
            entry_point = *(list_names.begin());
            std::vector<std::string> tmp(list_names);
            std::reverse(tmp.begin(), tmp.end());

            for (auto i = tmp.begin(); i != tmp.end(); ++i) {
                auto j = i;
                ++j;
                if (j == tmp.end()) {
                    return;
                }
                cooperation_groups[*(j)].async_send(
                        messaging::make_message(
                                std::string("sync_contacts"),
                                cooperation_groups[*(i)].address_entry_point()
                        )
                );
            }
        }

        void cooperation::sync() {
            if (cooperation_groups.size() == 1) {
                entry_point = cooperation_groups.begin()->first;
            }
        }

        cooperation &cooperation::add(group &&g) {
            cooperation_groups.emplace(g.name(), std::move(g));
            return *this;
        }

        void cooperation::async_send_all(messaging::message &&doc) {
            for (auto &i:cooperation_groups) {
                i.second.async_send_all(std::move(doc));
            }
        }


        cooperation &cooperation::add_sharet_address(actor::actor_address address) {
            for (auto &i:cooperation_groups) {
                i.second.add_shared_address(address);
            }
            return *this;
        }

        void cooperation::async_send(const std::string &name, messaging::message &&message) {
            cooperation_groups[name].async_send(std::move(message));
        }

        actor_zeta::actor::actor_address cooperation::get(const std::string & name) const {
            return actor_zeta::actor::actor_address(cooperation_groups.at(name).address_entry_point());
        }
    }
}