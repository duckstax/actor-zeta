#include "actor/behavior.hpp"
#include "environment/cooperation.hpp"
#include "actor/actor.hpp"
#include "environment/group.hpp"
#include "actor/local_actor.hpp"
#include <algorithm>

namespace actor_model {

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
                            std::string("sync_contacs"),
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

    cooperation::cooperation(std::initializer_list<actor_address> list) : sharet_contacts(list) {
    }

    cooperation &cooperation::add(group &&g) {
        cooperation_groups.emplace(g.name_entry_point(), std::move(g));
        return *this;
    }

    cooperation &cooperation::add(const std::string &key, abstract_actor *abstractActor) {
        cooperation_groups[key].add(abstractActor);
        return *this;
    }

    void cooperation::async_send_all(messaging::message &&doc) {
        for (auto &i:cooperation_groups) {
            i.second.async_send_all(std::move(doc));
        }
    }

    cooperation &cooperation::set_exeutor(const std::string &name_group, abstract_coordinator_ptr e) {
        cooperation_groups[name_group].set_exeutor_all(e);
        return *this;
    }

    cooperation &cooperation::set_exeutor_all(abstract_coordinator_ptr e) {
        for (auto &i:cooperation_groups) {
            i.second.set_exeutor_all(e);
        }
        return *this;
    }

    cooperation &cooperation::put_sharet(actor_address address) {
        for (auto &i:cooperation_groups) {
            i.second.add_shared(address);
        }
        return *this;
    }

    cooperation &cooperation::add(const std::string &name_group, actor &&a) {
        cooperation_groups[name_group].add(std::move(a));
        return *this;
    }

    void cooperation::async_send(const std::string &name, messaging::message &&message) {
        cooperation_groups[name].async_send(std::move(message));

    }
}