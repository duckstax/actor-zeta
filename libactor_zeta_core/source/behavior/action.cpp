#include "actor-zeta/behavior/action.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"


namespace actor_zeta {
    namespace behavior {

        action::action(abstract_action *aa) : action_impl_ptr(aa) {}

        response *action::operator()(request *request_){
            return action_impl_ptr->operator()(request_);
        }
    }
}