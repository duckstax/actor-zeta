#ifndef WRITE_HPP
#define WRITE_HPP

#include <map>
#include <iostream>
#include <actor-zeta/network/connection_identifying.hpp>
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace network {
        class write final : public behavior::interface_action {
        public:
            write(std::shared_ptr<multiplexer> multiplexer_) : multiplexer_(std::move(multiplexer_)), name_("write") {

            }

            void operator()(messaging::message *msg) override final {
                //name/blob data
                auto element = msg->get<std::pair<connection_identifying, std::string>>();
                multiplexer_->write(element.first, element.second);
            }

            const std::string &name() const final {
                return name_;
            };

        private:
            actor_zeta::network::shared_multiplexer_ptr multiplexer_;
            std::string name_;
        };
    }
}
#endif //WRITE_HPP
