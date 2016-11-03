#include "actor-zeta/standard_handlers/write.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace network {
        write::write(std::shared_ptr<multiplexer> multiplexer_)
                : multiplexer_(std::move(multiplexer_)), abstract_action("write") {}

        void write::operator()(messaging::message *msg) {
            //name/blob data
            auto element = msg->get<std::pair<connection_identifying, std::string>>();
            multiplexer_->write(element.first, element.second);
        }
    }
}