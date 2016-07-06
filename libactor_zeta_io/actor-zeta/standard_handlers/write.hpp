#ifndef WRITE_HPP
#define WRITE_HPP

#include <map>
#include <iostream>

namespace actor_zeta {
    namespace network {
        class write final : public behavior::abstract_action {
        public:
            write(std::map<std::string, write_handler> &actions) : actions(actions) {}

            void operator()(messaging::message &&msg) override {
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

            const std::string name() const {
                return std::string("write");
            };
        private:
            std::map<std::string, write_handler> &actions;
        };
    }
}
#endif //WRITE_HPP
