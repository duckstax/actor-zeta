#include "actor-zeta/standard_handlers/sync_contacts.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {

    sync_contacts::sync_contacts() :  abstract_action("sync_contacts") {}

    behavior::response *sync_contacts::operator()(behavior::request * request) {
        request->contacts().put(request->message()->get<actor::actor_address>());
        return nullptr;
    }
}