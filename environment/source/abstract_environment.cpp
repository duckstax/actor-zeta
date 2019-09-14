#include <actor-zeta/environment.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>

namespace actor_zeta { namespace environment {

        actor::supervisor &abstract_environment::manager_supervisor(detail::string_view name) {
            return *supervisors.at(name);
        }

        auto abstract_environment::create_supervisor(actor::supervisor *ptr) -> actor::supervisor & {
            supervisors.emplace(detail::string_view(""),intrusive_ptr<actor::supervisor>(ptr));
            return *ptr;
        }

        auto abstract_environment::graph() -> detail::storage_space {
            return storage_space_;
        }

    }}