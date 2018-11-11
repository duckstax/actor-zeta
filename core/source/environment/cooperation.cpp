#include <actor-zeta/environment/cooperation.hpp>

namespace actor_zeta {
    namespace environment {

        auto cooperation::created_group(actor::abstract_actor *t) -> group & {
            auto name = t->name();
            auto it = groups.emplace(name, group(new abstract_group(storage_space_, t)));
            return it.first->second;
        }

        auto link(group &g1, group &g2) -> void {
            g1->join(g2);
            g2->join(g1);
        }

        auto cooperation::created_entry_group(actor::abstract_actor *t) -> group & {
            auto &group = created_group(t);
            input_entry_point.push_back(group->id());
            return group;
        }

        auto cooperation::created_end_group(actor::abstract_actor *t) -> group & {
            auto &group = created_group(t);
            output_end_point.push_back(group->id());
            return group;
        }
    }
}