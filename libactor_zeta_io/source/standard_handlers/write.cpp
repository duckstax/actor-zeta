#include "actor-zeta/standard_handlers/write.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace network {
        write::write(shared_multiplexer_ptr  multiplexer_)
                : multiplexer_(multiplexer_), abstract_action("write") {}

        behavior::response *write::operator()(behavior::request * request ) {
                                                                //name/blob data
            auto element = request->message()->get<std::pair<connection_identifying, std::string>>();
            multiplexer_->write(element.first, element.second);
            return nullptr;
        }
    }
}