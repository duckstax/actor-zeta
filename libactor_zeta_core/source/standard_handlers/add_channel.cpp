#include "actor-zeta/standard_handlers/add_channel.hpp"

#include <iostream>

#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"
#include "actor-zeta/channel/channel.hpp"

namespace actor_zeta {

    void error(const std::string &name) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Not initialization channel type:" << name << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    add_channel::add_channel() : abstract_action("add_channel") {}

    behavior::response add_channel::operator()(behavior::request &&request) {
        auto channel_ = request.message().get<channel::channel>();
        if (channel_) {
            request.contacts().channel(channel_);
        } else {
            error(channel_->type());
        }

        return behavior::response();

    }
}