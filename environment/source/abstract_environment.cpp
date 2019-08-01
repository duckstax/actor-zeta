#include <actor-zeta/environment.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>

namespace actor_zeta { namespace environment {

    /*
        auto abstract_environment::created_group(actor::abstract_actor *t) -> actor::supervisor & {
            auto name = t->name();
            auto it = supervisors.emplace(name, new supervisor_heavy(this,storage_space_, t));
            return *(it.first->second);
        }
    */
        actor::supervisor &abstract_environment::manager_supervisor(detail::string_view name) {
            return *supervisors.at(name);
        }

        auto abstract_environment::create_supervisor(actor::supervisor *ptr) -> actor::supervisor & {
            supervisors.emplace(detail::string_view(""),intrusive_ptr<actor::supervisor>(ptr));
            return *ptr;
        }

    }}