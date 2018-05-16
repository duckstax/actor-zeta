#include <iostream>
#include <actor-zeta/standard_handlers/sync_contacts.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/behavior/context.hpp>

namespace actor_zeta {

    inline void error(const std::string& __error__){
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Not initialization actor_address type:" << __error__ << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    sync_contacts::sync_contacts() :  abstract_action("sync_contacts") {}

    void sync_contacts::invoke(behavior::context & context_) {
        auto address = context_.message().get<actor::actor_address>();

        if(address){
            context_->address(address);
        } else {
            error(address->name());
        }
    }
}