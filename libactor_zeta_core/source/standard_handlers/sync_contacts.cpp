#include <iostream>
#include "actor-zeta/standard_handlers/sync_contacts.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"
#include "actor-zeta/actor/actor_address.hpp"

namespace actor_zeta {

    sync_contacts::sync_contacts() :  abstract_action("sync_contacts") {}

    behavior::response *sync_contacts::operator()(behavior::request * request) {
        auto address=request->message()->get<actor::actor_address>();
        if(address){
            request->contacts().address(address);
        } else {
            std::cerr << "WARNING" << std::endl;
            std::cerr << "Not initialization actor_address type:" << address->type() << std::endl;
            std::cerr << "WARNING" << std::endl;
        }
        return nullptr;
    }
}