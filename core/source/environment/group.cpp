#include "actor/local_actor.hpp"
#include "environment/group.hpp"
#include <algorithm>

namespace actor_zeta {

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

    actor_address group::address_entry_point() {
        return unique_actors[entry_point].address();
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

    group &group::add_shared_address(actor_address address) {
        for (auto &i:unique_actors)
            i.second->async_send(
                    messaging::make_message(
                            std::string("sync_contacts"),
                            address
                    )
            );
        return *this;
    }

    group &group::add(abstract_actor *aa) {
        unique_actors.emplace(aa->type(), actor(aa));
        return *this;
    };

    group &group::set_exeutor(const std::string &name_actor, abstract_coordinator_ptr e) {
        unique_actors[name_actor]->attach(e);
        return *this;
    }


    group &group::set_exeutor_all(abstract_coordinator_ptr e) {
        for (auto &i:unique_actors) {
            i.second->attach(e);
        }
        return *this;
    }

    group &group::add(actor &&a) {
        unique_actors.emplace(a.type(), std::move(a));
        return *this;
    }

    void group::sync() {
        if(unique_actors.size()==1){
            entry_point = (*unique_actors.begin()).first;
        }

    }

    group &group::add(const std::string &root_name, abstract_actor *aa) {
        actor_zeta::actor_address address =aa->adddres();
        unique_actors.emplace(aa->type(), actor(aa));
        unique_actors[root_name]->async_send(
                messaging::make_message(
                        std::string("sync_contacts"),
                        address
                )
        );
        return *this;
    }

    group::group(abstract_actor *aa) {
        std::string entry_address =aa->type();
        unique_actors.emplace(aa->type(), actor(aa));
        entry_point =entry_address;
    }
}