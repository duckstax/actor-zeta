#ifndef WRITE_HPP
#define WRITE_HPP

#include <map>
#include <iostream>

#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace network {
        class write final : public behavior::interface_action {
        public:
            write(std::unordered_map<std::string, write_handler> &actions) : actions(actions),name_("write") {}

            void operator()(messaging::message &&msg) override final {
                //name/blob data
                auto element = msg.get<std::pair<std::string, std::string>>();
                auto it = actions.find(element.first);
                if (it != actions.end()) {
                    auto wh = *(it);
                    wh.second(element.second);
                }
                else {
                    std::cerr << "Error Not Method" << std::endl;
                }
            }

            const std::string& name() const final {
                return name_;
            };
        private:
            std::unordered_map<std::string, write_handler> &actions;
            std::string name_;
        };
    }
}
#endif //WRITE_HPP
